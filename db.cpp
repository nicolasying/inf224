#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <memory>
#include "db.h"
#include "error.h"

using namespace std;
using namespace cppu;

const string DB::reqSearch = "SEARCH";
const string DB::reqPlay = "PLAY";
const string DB::reqDelete = "DELETE";

MulPtr DB::createPhoto(const std::string _name, const std::string _path, const double _latitude, const double _longitude) {
    if (media.find(_name) != media.end()) {
        throw NameConflict(_name);
        cout << "DB: Media with the same name already exists." << endl;
    } else {
        media[_name] = make_shared<Photo>(_name, _path, _latitude, _longitude);
    }
    return media[_name];
}

MulPtr DB::createVideo(const std::string _name, const std::string _path, const int _duration) {
    if (media.find(_name) != media.end()) {
        throw NameConflict(_name);
        cout << "DB: Media with the same name already exists." << endl;
    } else {
        media[_name] = make_shared<Video>(_name, _path, _duration);
    }
    return media[_name];
}

MulPtr DB::createFilm(const std::string _name, const std::string _path, const int _duration, const int _nChap, const int * const _chapterTable) {
    if (media.find(_name) != media.end()) {
        throw NameConflict(_name);
        cout << "DB: Media with the same name already exists." << endl;
    } else {
        media[_name] = make_shared<Film>(_name, _path, _duration, _nChap, _chapterTable);
    }
    return media[_name];
}

GrPtr DB::createGroup(const std::string _gName) {
    if (groups.find(_gName) != groups.end()) {
        throw NameConflict(_gName);
        cout << "DB: Group with the same name already exists." << endl;
    } else {
        groups[_gName] = make_shared<Group>(_gName);
    }
    return groups[_gName];
}

void DB::searchMedia(const std::string _name, ostream& _optScr) {
    auto md = media.find(_name);
    if (md == media.end()) {
        _optScr << "DB: Media with the same name does not exist." << endl;
        return;
    } else {
        md->second->display(_optScr);
        return;
    }
}

void DB::searchGroup(const std::string _name, ostream& _optScr) {
    auto md = groups.find(_name);
    if (md == groups.end()) {
        _optScr << "DB: Group with the same name does not exist." << endl;
        return;
    } else {
        md->second->display(_optScr);
        return;
    }
}
void DB::playMedia(const std::string _name) {
    auto md = media.find(_name);
    if (md == media.end()) {
        cout << "DB: Media with the same name does not exist." << endl;
        return;
    } else {
        md->second->play();
        return;
    }
}

void DB::deleteMedia(const std::string _name) {
    auto md = media.find(_name);
    if (md == media.end()) {
        cout << "DB: Media with the same name does not exist." << endl;
        return;
    } else {
        media.erase(md);
        return;
    }
}

void DB::deleteGroup(const std::string _name) {
    auto md = groups.find(_name);
    if (md == groups.end()) {
        cout << "DB: Group with the same name does not exist." << endl;
        return;
    } else {
        groups.erase(md);
        return;
    }
}

bool DB::processRequest(TCPConnection& cnx, const string& request, string& response) {
    cerr << "\nRequest: '" << request << "'" << endl;

    // 1) pour decouper la requête:
    // on peut par exemple utiliser stringstream et getline()
    
    
    // 2) faire le traitement:
    // - si le traitement modifie les donnees inclure: TCPLock lock(cnx, true);
    // - sinon juste: TCPLock lock(cnx);


    // 3) retourner la reponse au client:
    // - pour l'instant ca retourne juste OK suivi de la requête
    // - pour retourner quelque chose de plus utile on peut appeler la methode print()
    //   des objets ou des groupes en lui passant en argument un stringstream
    // - attention, la requête NE DOIT PAS contenir les caractères \n ou \r car
    //   ils servent à délimiter les messages entre le serveur et le client
    
    size_t del = request.find(" ");
    string req, name;
    if (del != string::npos) {
        req = request.substr(0, del);
        name = request.substr(del+1);
        stringstream resBuf;
        if (req.compare(DB::reqSearch) == 0) {
            TCPLock lock(cnx);
            resBuf << "OK: " << endl << "Group Search Results: " << endl;
            searchGroup(name, resBuf);
            resBuf << endl << "Media Search Results: " << endl;
            searchMedia(name, resBuf);
        } else if (req.compare(DB::reqPlay) == 0) {
            TCPLock lock(cnx);
            resBuf << "OK: " << endl << "Media Played on Server." << endl;
            playMedia(name);
        } else if (req.compare(DB::reqDelete) == 0) {
            TCPLock lock(cnx, true);
            resBuf << "PLACEHOLDER: " << endl << "DELETE." << endl;
        } else {
            resBuf << "ERROR: UNSUPPORTED REQUEST" << endl;
        }
        response = resBuf.str();
    } else {
        response = "ERROR: ILLEGAL REQUEST";
    }
    
    cerr << "response: " << response << endl;
    replace(response.begin(), response.end(), '\n', ';');
    // renvoyer false si on veut clore la connexion avec le client
    return true;
}
