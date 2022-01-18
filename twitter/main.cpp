#include <iostream>
#include <set>
#include <map>
#include <memory>
#include <ostream>
#include <sstream>

class MessageException : public std::runtime_error {
  public:
    MessageException(std::string message): runtime_error(message) {}
};

class Message {
  private:
    int id;
    std::string username;
    std::string message;
    std::set<std::string> likes;

  public:
    Message(int id = 0, std::string username = "", std::string message = "") {
      this->id = id;
      this->username = username;
      this->message = message;
    }
    ~Message() {}

    int getId() {
      return this->id;
    }

    void like(std::string username) {
      this->likes.insert(username);
    }

    friend std::ostream& operator <<(std::ostream& os, const Message& message) {
      os << message.id << ":" << message.username << " (" << message.message << ")";

      if (message.likes.size() > 0) {
        os << " [";
        auto it = message.likes.begin();
        while(it != message.likes.end()) {
          if (it != message.likes.begin()) {
            os << ", " << *it;
          } else {
            os << *it;
          } 

          it++;
        }
        os << "]";
      }

      return os;
    }
};

class Inbox {
  private:
    std::map<int, Message*> messagesUnread;
    std::map<int, Message*> allMessages;

  public:
    Inbox() {}
    ~Inbox() {}

    void storeUnread(Message* tweet) {
      this->messagesUnread.insert(std::make_pair(tweet->getId(), tweet));
      this->allMessages.insert(std::make_pair(tweet->getId(), tweet));
    }

    void storeReaded(Message* tweet) {
      this->allMessages.insert(std::make_pair(tweet->getId(), tweet));
    }

    std::map<int, Message*> getMessagesUnread() {
      auto messagesUnreadOld = this->messagesUnread;
      this->messagesUnread.clear();
      return messagesUnreadOld;
    }

    std::map<int, Message*> getAll() const {
      return this->allMessages;
    }

    Message* getTweet(int id) {
      auto it = this->allMessages.find(id);

      if (it == allMessages.end()) {
        throw MessageException("tweet nao encontrado");
      }

      return it->second;
    }

    friend std::ostream& operator <<(std::ostream& os, const Inbox& inbox) {
      for (auto [id, message] : inbox.allMessages) {
        os << *message << "\n";
      }

      return os;
    }
};

class User{
  private:
    std::string username;
    std::map<std::string, User*> followers;
    std::map<std::string, User*> following;
    Inbox* inbox;
  
  public:
    User(std::string username = "") {
      this->username = username;
      this->inbox = new Inbox();
    }
    ~User() {}

    void follow(User* other) {
      auto it = this->following.find(other->username);

      if (it != this->following.end()) {
        throw MessageException(this->username + " ja segue esse usuario");
      }

      this->following.insert(std::make_pair(other->username, other));
      other->followers.insert(std::make_pair(this->username, this));
    }

    void unfollow(User* other) {
      auto userFollowed = this->following.find(other->username);

      if (userFollowed == this->following.end()) {
        throw MessageException(this->username + " nao segue esse usuario");
      }

      other->followers.erase(this->username);
      this->following.erase(other->username);
    }

    void like(int tweetId) {
      auto tweet = this->inbox->getTweet(tweetId);
      tweet->like(this->username);
    }
    
    Inbox* getInbox() {
      return this->inbox;
    }

    void sendTweet(Message* tweet) {
      this->inbox->storeReaded(tweet);
      
      for (auto [username, user] : this->followers) {
        user->inbox->storeUnread(tweet);
      }
    }

    //show all followers and following by name
    friend std::ostream& operator <<(std::ostream& os, const User& user) {
      os << user.username << "\n";

      os << "  segue [";
      auto itFollowing = user.following.begin();
      while(itFollowing != user.following.end()) {
        if (itFollowing != user.following.begin()) {
          os << ", " << itFollowing->first;
        } else {
          os << itFollowing->first;
        } 

        itFollowing++;
      }
      os << "]\n";

      os << "  seguidores [";
      auto itFollowers = user.followers.begin();
      while(itFollowers != user.followers.end()) {
        if (itFollowers != user.followers.begin()) {
          os << ", " << itFollowers->first;
        } else {
          os << itFollowers->first;
        } 

        itFollowers++;
      }
      os << "]";

      return os;
    }
};

class Controller {
  private:
    std::map<std::string, User*> users;
    std::map<int, Message*> tweets;
    int nextTweetId = 1;
  
  public:
    Controller() {}

    void addUser(std::string username) {
      auto it = this->users.find(username);

      if (it != this->users.end()) {
        throw MessageException("usuario ja existe");
      }
      
      this->users.insert(std::make_pair(username, new User(username)));
    }

    User* getUser(std::string username) {
      auto it = this->users.find(username);

      if (it == this->users.end()) {
        throw MessageException("usuario nao encontrado");
      }

      return this->users[username];
    }

    void sendTweet(std::string username, std::string message) {
      auto user = this->getUser(username);
      Message* tweet = new Message(nextTweetId, username, message);

      user->sendTweet(tweet);
      this->tweets.insert(std::make_pair(tweet->getId(), tweet));
      this->nextTweetId++;
    }

    friend std::ostream& operator <<(std::ostream& os, const Controller& controller) {
      for (auto [username, user] : controller.users) {
        os << *user << "\n";
      }

      return os;
    }
};

int main() {
  Controller controller;

  while(true) {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::string cmd;
    ss >> cmd;
    
    try {
      if(cmd == "end") {
        break;
      } else if(cmd == "help") {
          std::cout << "init;\n"
            << "show;\n"
            << "addUser _username;\n"
            << "follow _username _followUsername;\n"
            << "unfollow _username _unfollowUsername;\n"
            << "twittar _username _message;\n"
            << "like _username _idTweet;\n"
            << "timeline _username;\n"
            << "unread _username;\n"
            << "end;\n";
      } else if(cmd == "init") {
        controller = Controller();
      } else if(cmd == "show") {
        std::cout << controller << "\n";
      } else if(cmd == "addUser") {
        std::string username;
        ss >> username;

        controller.addUser(username);
      } else if(cmd == "follow") {
        std::string username;
        std::string usernameFollow;
        ss >> username >> usernameFollow;
        
        auto user = controller.getUser(username);
        user->follow(controller.getUser(usernameFollow));
      } else if(cmd == "unfollow") {
        std::string username;
        std::string usernameUnfollow;
        ss >> username >> usernameUnfollow;
        
        auto user = controller.getUser(username);
        user->unfollow(controller.getUser(usernameUnfollow));
      } else if(cmd == "twittar") {
        std::string username;
        std::string message;
        ss >> username;
        std::getline(ss, message);

        controller.sendTweet(username, message);
      } else if(cmd == "like") {
        std::string username;
        int idTweet;
        ss >> username >> idTweet;
        
        auto user = controller.getUser(username);
        user->like(idTweet);
      } else if(cmd == "timeline") {
        std::string username;
        ss >> username;
        
        auto user = controller.getUser(username);
        std::cout << *user->getInbox() << "\n";
      } else if(cmd == "unread") {
        std::string username;
        ss >> username;
        
        auto user = controller.getUser(username);
        std::cout << user << "\n";
      } else {
        std::cout << "fail: comando invalido\n";
      }
    } catch (MessageException& e) {
      std::cout << "fail: " << e.what() << "\n";
    }
  }
}