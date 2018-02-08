import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.Socket;
import java.net.UnknownHostException;

public class Remote extends JFrame {
    private static final long serialVersionUID = 1L;

    JMenuBar menuBar;
    JMenu menu;
    JToolBar toolBar;
    JPanel bHolder;
    JTextArea txt;
    JTextField requestField;
    JButton b1, b2, b3, bExit;

    static final String DEFAULT_HOST = "localhost";
    static final int DEFAULT_PORT = 3332;
    private Socket sock;
    private BufferedReader input;
    private BufferedWriter output;

    public static void main(String[] argv) {
        if (System.getProperty("os.name").contains("mac")) {
            System.setProperty("apple.laf.useScreenMenuBar", "true");
        }

        String host = DEFAULT_HOST;
        int port = DEFAULT_PORT;
        if (argv.length >=1) host = argv[0];
        if (argv.length >=2) port = Integer.parseInt(argv[1]);

        Remote client = null;

        try {
            client = new Remote(host, port);
        }
        catch (Exception e) {
            System.err.println("Client: Couldn't connect to "+host+":"+port);
            System.exit(1);
        }
    }

    public Remote(String host, int port) throws UnknownHostException, IOException {

        setMinimumSize(new Dimension(800, 600));

        menuBar = new JMenuBar();
        menu = new JMenu("Menu");

        toolBar = new JToolBar();

        txt = new JTextArea();
        txt.setRows(10);

        requestField = new JTextField();

        bHolder = new JPanel();
        bHolder.setLayout(new GridLayout());
        b1 = new JButton("SEARCH");
        b2 = new JButton("PLAY");
        b3 = new JButton("LIST");
        bExit = new JButton("Exit");

        menuBar.add(menu);
        menuBar.add(toolBar);

        class MyButton1 extends AbstractAction {
            public MyButton1(String name) {
                super(name);
            }

            public void actionPerformed(ActionEvent e) {
                String mediaName = requestField.getText();
                if (mediaName.length() == 0) {
                    txt.setText("Enter query.\n");
                } else {
                    txt.setText("\nRequest to searching for " + mediaName + ".\n");
                    String request = "SEARCH " + mediaName;
                    String response = send(request);
                    response = response.replace(';', '\n');
                    txt.append("Response from server: " + response);
                }
            }
        }

        class MyButton2 extends AbstractAction {
            public MyButton2(String name) {
                super(name);
            }

            public void actionPerformed(ActionEvent e) {
                String mediaName = requestField.getText();
                if (mediaName.length() == 0) {
                    txt.setText("Enter query.\n");
                } else {
                    txt.setText("\nRequest to play " + mediaName + ".\n");
                    String request = "PLAY " + mediaName;
                    String response = send(request);
                    response = response.replace(';', '\n');
                    txt.append("Response from server: " + response);
                }
            }
        }

        class MyButton3 extends AbstractAction {
            public MyButton3(String name) {
                super(name);
            }

            public void actionPerformed(ActionEvent e) {
                txt.setText("\nRequest to list all media.\n");
                String request = "LIST";
                String response = send(request);
                response = response.replace(';', '\n');
                txt.append("Response from server: " + response);
            }
        }

        class MyButton4 extends AbstractAction {
            public MyButton4(String name) {
                super(name);
            }

            public void actionPerformed(ActionEvent e) {
                txt.setText("\nRequest to list all media.\n");
                String request = "SERIAL";
                String response = send(request);
                response = response.replace(';', '\n');
                txt.append("Response from server: " + response);
            }
        }

        class MyButtonExit extends AbstractAction {
            public MyButtonExit(String name) {
                super(name);
            }

            public void actionPerformed(ActionEvent e) {
                System.exit(5);
            }
        }

        MyButton1 a1 = new MyButton1("SEARCH");
        MyButton2 a2 = new MyButton2("PLAY");
        MyButton3 a3 = new MyButton3("LIST");
        MyButton4 a4 = new MyButton4("DUMP");
        MyButtonExit aE = new MyButtonExit("EXIT");

        b1.addActionListener(a1);
        b2.addActionListener(a2);
        b3.addActionListener(a3);
        bExit.addActionListener(aE);
        bHolder.add(requestField);
        bHolder.add(b1);
        bHolder.add(b2);
        bHolder.add(b3);
        bHolder.add(bExit);
        toolBar.add(a1);
        toolBar.add(a2);
        toolBar.add(a3);
        toolBar.add(a4);
        toolBar.add(aE);
        menu.add(a1);
        menu.add(a2);
        menu.add(a3);
        menu.add(a4);
        menu.add(aE);


        setJMenuBar(menuBar);

        add(txt, BorderLayout.CENTER);
        add(bHolder, BorderLayout.SOUTH);

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setTitle("Media Centre");
        pack();
        setVisible(true);

        try {
            sock = new java.net.Socket(host, port);
        }
        catch (java.net.UnknownHostException e) {
            txt.setText("Client: Couldn't find host "+host+":"+port);
            throw e;
        }
        catch (java.io.IOException e) {
            txt.setText("Client: Couldn't reach host "+host+":"+port);
            throw e;
        }

        try {
            input = new BufferedReader(new InputStreamReader(sock.getInputStream()));
            output = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()));
        }
        catch (java.io.IOException e) {
            txt.setText("Client: Couldn't open input or output streams");
            throw e;
        }

        System.out.println("Client connected to "+host+":"+port);
    }

    public String send(String request) {
        // Envoyer la requete au serveur
        try {
            request += "\n";  // ajouter le separateur de lignes
            output.write(request, 0, request.length());
            output.flush();
        }
        catch (java.io.IOException e) {
            txt.setText("Client: Couldn't send message: " + e);
            return null;
        }

        // Recuperer le resultat envoye par le serveur
        try {
            return input.readLine();
        }
        catch (java.io.IOException e) {
            txt.setText("Client: Couldn't receive message: " + e);
            return null;
        }
    }
}

