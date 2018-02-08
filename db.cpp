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
const string DB::reqList = "LIST";
const string DB::reqSerial = "SERIAL";

const int PROTOCOL = 1;
const string MEDIA_BEGIN = "__BEGIN_MEDIA__";
const string MEDIA_END = "__END_MEDIA__";
const string GROUP_BEGIN = "__BEGIN_GROUP__";
const string GROUP_END = "__END_GROUP__";

int atoi(string _s) {
    return atoi(_s.c_str());
}

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

void DB::listAll(ostream& _optScr) {
    _optScr << "DB: Listing groups." << endl;
    for (auto & it : groups) {
        _optScr << it.first << ", ";
    }
    _optScr << endl << "DB: Listing media." << endl;
    for (auto & it : media) {
        _optScr << it.first << ", ";
    }
    _optScr << endl;
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
    stringstream resBuf;
    if (del != string::npos) {
        req = request.substr(0, del);
        name = request.substr(del+1);
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
    } else if (request.compare(DB::reqList) == 0) {
        TCPLock lock(cnx);
        resBuf << "OK: " << endl << "Delaying request." << endl;
        listAll(resBuf);
        response = resBuf.str();
    } else if (request.compare(DB::reqSerial) == 0) {
        TCPLock lock(cnx);
        resBuf << "OK: " << endl << "Delaying request." << endl;
        resBuf << *this;
        response = resBuf.str();
    } else {
        response = "ERROR: ILLEGAL REQUEST";
    }
    
    cerr << "response: " << response << endl;
    replace(response.begin(), response.end(), '\n', ';');
    // renvoyer false si on veut clore la connexion avec le client
    return true;
}


ostream& operator<< (ostream& os, const DB& db) {
    os << "PROTOCOL V " << PROTOCOL << endl;
    os << MEDIA_BEGIN << endl;
    for (auto & it : db.media) {
        os << it.first << endl << *(it.second.get()) << endl;
    }
    os << MEDIA_END << endl;
    return os;
}

istream& operator>> (istream& is, DB& db) {
    string buff;

    // check compatibility
    getline(is, buff);
    int targetV = atoi(buff.substr(buff.find_last_of(" ")+1));
    if (targetV != PROTOCOL) {
        throw Incompatibility(targetV, PROTOCOL);
        return is;
    } 
    
    // section detection
    getline(is, buff);
    if (buff.compare(MEDIA_BEGIN) == 0) {
        try{
            while(getline(is, buff)) { // buff = name in db
                string name, path;
                name = buff;
                getline(is, buff); // buff = type
                if(buff.compare("Photo") == 0) {
                    getline(is, buff); // buff = name in object
                    getline(is, path);
                    int _latitude, _longitude;
                    getline(is, buff); // buff = latitude
                    _latitude = atoi(buff);
                    getline(is, buff); // buff = longtitude
                    _longitude = atoi(buff);
                    db.createPhoto(name, path, _latitude, _longitude);
                } else if (buff.compare("Video") == 0) {
                    getline(is, buff); // buff = name in object
                    getline(is, path);
                    int _length;
                    getline(is, buff); // buff = length
                    _length = atoi(buff);
                    db.createVideo(name, path, _length);
                } else if (buff.compare("Film") == 0) {
                    getline(is, buff); // buff = name in object
                    getline(is, path);
                    int _length, nChap;
                    getline(is, buff); // buff = length
                    _length = atoi(buff);
                    getline(is, buff); // buff = nChap
                    nChap = atoi(buff);
                    int chaps[nChap];
                    for (int i = 0; i < nChap; i++) {
                        getline(is, buff); // buff = stamp
                        chaps[i] = atoi(buff);
                    }
                    db.createFilm(name, path, _length, nChap, chaps);
                } else {
                    throw UnknownClass(buff);
                }
                getline(is, buff); // clear the marge
            }
        } catch (UnknownClass& c) {
            if (c.className.compare(MEDIA_END) == 0) {
                return is;
            } else {
                throw c;
                return is;
            }
        } catch (ios::failure& e) {
            return is;
        }
    } else {
        throw SerialParseError(buff);
        return is;
    }
}