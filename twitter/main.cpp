#include <iostream>
#include <set>
#include <map>
#include <memory>
#include <regex>
#include <ostream>
#include <sstream>
#include "utils.hpp"

class TweetException : public std::exception {
    std::string message;
public:
    TweetException(const std::string& message) : 
        message(message) {
    }
    const char* what() const noexcept override {
        return message.c_str(); 
    }
};

class Tweet {
  private:
    int id;
    std::string username;
    std::string message;
    std::set<std::string> likes;
    Tweet* retweet;
    bool deleted;

  public:
    Tweet(int id = 0, std::string username = "", std::string message = "") {
      this->id = id;
      this->username = username;
      this->message = message;
      this->retweet = nullptr;
      this->deleted = false;
    }

    ~Tweet() {}

    int getId() const {
      return this->id;
    }

    std::string getSender() const {
      return this->username;
    }

    std::string getMessage() const {
      return this->message;
    }

    std::set<std::string> getLikes() const {
      return this->likes;
    }

    bool isDeleted() const {
      return this->deleted;
    }

    void setRetweet(Tweet* retweet) {
      this->retweet = retweet;
    }

    void setDeleted() {
      if (this->deleted) {
        throw new TweetException("esse tweet ja foi deletado");
      }

      this->username = "";
      this->message = "esse tweet foi deletado";
      this->likes.clear();
      this->deleted = true;
    }

    void like(std::string username) {
      this->likes.insert(username);
    }

    friend std::ostream& operator <<(std::ostream& os, const Tweet& tweet) {
      os << tweet.id << ":" << tweet.username << " (" << tweet.message << ")";

      if (tweet.likes.size() > 0) {
        os << " [";
        auto it = tweet.likes.begin();
        while(it != tweet.likes.end()) {
          if (it != tweet.likes.begin()) {
            os << ", " << *it;
          } else {
            os << *it;
          } 

          it++;
        }
        os << "]";
      }

      if (tweet.retweet != nullptr) {
        os << "\n  ";
        os << *tweet.retweet << "\n";
      }

      return os;
    }
};

class Inbox {
  private:
    std::map<int, Tweet*> timeline;
    std::map<int, Tweet*> myTweets;

  public:
    Inbox() {
      this->timeline = {};
      this->myTweets = {};
    }

    ~Inbox() {}

    std::vector<Tweet*> getTimeline() const {
      std::vector<Tweet*> timelineSorted;

      for (auto [id, tweet] : this->timeline) {
        timelineSorted.push_back(tweet);
      }

      std::sort(timelineSorted.begin(), timelineSorted.end(), [](Tweet* tweet1, Tweet* tweet2){
        return tweet1->getId() > tweet2->getId();
      });

      return timelineSorted;
    }

    std::vector<Tweet*> getMyTweets() const {
      std::vector<Tweet*> myTweetsSorted;

      for (auto [id, tweet] : this->myTweets) {
        myTweetsSorted.push_back(tweet);
      }

      std::sort(myTweetsSorted.begin(), myTweetsSorted.end(), [](Tweet* tweet1, Tweet* tweet2){
        return tweet1->getId() > tweet2->getId();
      });

      return myTweetsSorted;
    }

    Tweet* getTweet(int id) const {
      auto it = this->timeline.find(id);

      if (it == this->timeline.end()) {
        throw TweetException("tweet nao encontrado");
      }

      return it->second;
    }

    void storeInTimeline(Tweet* tweet) {
      this->timeline.insert(std::make_pair(tweet->getId(), tweet));
    }

    void storeInMyTweets(Tweet* tweet) {
      this->myTweets.insert(std::make_pair(tweet->getId(), tweet));
    }

    void removeMessagesFrom(std::string username) {
      auto oldTimeline = this->timeline;
      for (auto [id, tweet] : oldTimeline) {
        if (username == tweet->getSender()) {
          this->timeline.erase(id);
        }
      }
    }

    friend std::ostream& operator <<(std::ostream& os, const Inbox& inbox) {
      auto timeline = inbox.getTimeline();
      for (auto tweet : timeline) {
        os << *tweet << "\n";
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
      this->followers = {};
      this->following = {};
      this->inbox = new Inbox();
    }

    ~User() {}

    Inbox* getInbox() {
      return this->inbox;
    }

    Tweet* getTweet(int tweetId) const {
      return this->inbox->getTweet(tweetId);
    }

    void follow(User* other) {
      if (this == other) {
        throw TweetException("voce nao pode seguir a si mesmo");
      }

      auto it = this->following.find(other->username);
      if (it != this->following.end()) {
        throw TweetException(this->username + " ja segue esse usuario");
      }

      this->following.insert(std::make_pair(other->username, other));
      other->followers.insert(std::make_pair(this->username, this));
    }

    void unfollow(std::string username) {
      auto userFollowed = this->following.find(username);

      if (userFollowed == this->following.end()) {
        throw TweetException(this->username + " nao segue esse usuario");
      }

      userFollowed->second->followers.erase(this->username);
      this->inbox->removeMessagesFrom(username);
      this->following.erase(username);
    }

    void unfollowAll() {
      auto oldFollowing = this->following;
      for (auto [username, user] : oldFollowing) {
        user->unfollow(this->username);
        this->unfollow(user->username);
      }
    }

    void rejectAll() {
      auto oldFollowers = this->followers;
      for (auto [username, user] : oldFollowers) {
        user->unfollow(this->username);
        this->unfollow(user->username);
      }
    }

    void like(int tweetId) {
      auto tweet = this->inbox->getTweet(tweetId);
      tweet->like(this->username);
    }

    void sendTweet(Tweet* tweet) {
      this->inbox->storeInMyTweets(tweet);
      this->inbox->storeInTimeline(tweet);
      
      for (auto [username, user] : this->followers) {
        user->inbox->storeInTimeline(tweet);
      }
    }

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
    std::map<int, Tweet*> tweets;
    int nextTweetId;
  
  public:
    Controller() {
      this->nextTweetId = 1;
      this->users = {};
      this->tweets = {};
    }

    User* getUser(std::string username) {
      auto it = this->users.find(username);

      if (it == this->users.end()) {
        throw TweetException("usuario nao encontrado");
      }

      return this->users[username];
    }

    Tweet* getTweet(int tweetId) {
      auto it = this->tweets.find(tweetId);

      if (it == this->tweets.end()) {
        throw TweetException("tweet nao encontrado");
      }

      return this->tweets[tweetId];
    }

    void addUser(std::string username) {
      auto it = this->users.find(username);

      if (it != this->users.end()) {
        throw TweetException("usuario ja existe");
      }

      User* user = new User(username);
      this->users.insert(std::make_pair(username, user));
    }

    void removeUser(std::string username) {
      auto user = this->getUser(username);
      user->unfollowAll();
      user->rejectAll();

      auto myTweets = user->getInbox()->getMyTweets();
      for (auto tweet : myTweets) {
        tweet->setDeleted();
      }

      this->users.erase(username);
    }

    void sendTweet(std::string username, std::string message) {
      auto user = this->getUser(username);
      Tweet* tweet = new Tweet(nextTweetId, username, message);

      user->sendTweet(tweet);
      this->tweets.insert(std::make_pair(tweet->getId(), tweet));
      this->nextTweetId++;
    }

    void sendRetweet(std::string username, int tweetId, std::string message) {
      auto user = this->getUser(username);
      auto tweet = user->getTweet(tweetId);
      Tweet* retweet = new Tweet(nextTweetId, username, message);
      retweet->setRetweet(tweet);

      this->tweets.insert(std::make_pair(retweet->getId(), retweet));
      this->nextTweetId++;
      user->sendTweet(retweet);
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
    auto params = utils::split(line, ' ');
    auto cmd = params[0];
    
    try {
      if(cmd == "end") {
        break;
      } else if(cmd == "help") {
          std::cout << "show;\n"
            << "addUser _username;\n"
            << "removeUser _username;\n"
            << "follow _username _followUsername;\n"
            << "unfollow _username _unfollowUsername;\n"
            << "twittar _username _message;\n"
            << "retwittar _username _idTweet _message;\n"
            << "like _username _idTweet;\n"
            << "timeline _username;\n"
            << "unread _username;\n"
            << "end;\n";
      } else if(cmd == "show") {
        std::cout << controller << "\n";
      } else if(cmd == "addUser") {
        controller.addUser(params[1]);
      } else if(cmd == "removeUser") {
        controller.removeUser(params[1]);
      } else if(cmd == "follow") {
        auto user = controller.getUser(params[1]);
        user->follow(controller.getUser(params[2]));
      } else if(cmd == "unfollow") {
        auto user = controller.getUser(params[1]);
        user->unfollow(params[2]);
      } else if(cmd == "twittar") {
        auto message = utils::slice(params, 2);
        controller.sendTweet(params[1], utils::join(message, " "));
      } else if(cmd == "retwittar") {
        auto message = utils::slice(params, 3);
        controller.sendRetweet(params[1], std::stoi(params[2]), utils::join(message, " "));
      } else if(cmd == "like") {
        auto user = controller.getUser(params[1]);
        user->like(std::stoi(params[2]));
      } else if(cmd == "timeline") {
        auto user = controller.getUser(params[1]);
        std::cout << *user->getInbox() << "\n";
      } else {
        std::cout << "fail: comando invalido\n";
      }
    } catch (TweetException& e) {
      std::cout << "fail: " << e.what() << "\n";
    }
  }
}