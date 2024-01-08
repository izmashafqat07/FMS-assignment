#include <iostream>
#include <vector>
#include <string>
#include <limits> // Include for handling invalid input

class Property {
protected:
    std::string location;
    double price;

public:
    Property(const std::string& loc, double pr) : location(loc), price(pr) {}

    virtual void display() const = 0;
    virtual double calculateBill() const = 0;

    std::string getLocation() const { return location; }
    double getPrice() const { return price; }
};

class ResidentialProperty : public Property {
private:
    int bedrooms;

public:
    ResidentialProperty(const std::string& loc, double pr, int beds)
        : Property(loc, pr), bedrooms(beds) {}

    void display() const override {
        std::cout << "Residential Property: " << location << ", Bedrooms: " << bedrooms << ", Price: $" << price << std::endl;
    }

    double calculateBill() const override {
        // Return the original price without any additional tax
        return price;
    }
};

class CommercialProperty : public Property {
private:
    std::string businessType;

public:
    CommercialProperty(const std::string& loc, double pr, const std::string& type)
        : Property(loc, pr), businessType(type) {}

    void display() const override {
        std::cout << "Commercial Property: " << location << ", Business Type: " << businessType << ", Price: $" << price << std::endl;
    }

    double calculateBill() const override {
        // Return the original price without any additional tax
        return price;
    }
};

class User {
protected:
    std::string username;
    std::string userType;

public:
    User(const std::string& uname, const std::string& type) : username(uname), userType(type) {}

    virtual void display() const {
        std::cout << userType << " User: " << username << std::endl;
    }

    const std::string& getUsername() const {
        return username;
    }

    const std::string& getUserType() const {
        return userType;
    }
};

class Buyer : public User {
private:
    std::vector<Property*> ownedProperties;
    double totalBill;

public:
    Buyer(const std::string& uname) : User(uname, "Buyer"), totalBill(0.0) {}

    void display() const override {
        User::display();
        std::cout << "Owned Properties:" << std::endl;
        for (const auto& property : ownedProperties) {
            property->display();
        }
        std::cout << "Total Bill: $" << totalBill << std::endl;
    }

    void buyProperty(Property* property) {
        ownedProperties.push_back(property);
        totalBill += property->calculateBill();
    }

    double calculateTotalBill() const {
        return totalBill;
    }
};

class Seller : public User {
private:
    std::vector<Property*> listedProperties;

public:
    Seller(const std::string& uname) : User(uname, "Seller") {}

    void display() const override {
        User::display();
        std::cout << "Listed Properties:" << std::endl;
        for (const auto& property : listedProperties) {
            property->display();
        }
    }

    void listProperty(Property* property) {
        listedProperties.push_back(property);
    }

    void removeProperty(Property* property) {
        // Implement removal logic
    }

    const std::vector<Property*>& getListedProperties() const {
        return listedProperties;
    }
};

class RealEstatePlatform {
private:
    std::vector<User*> users;
    std::vector<Property*> properties;

public:
    void addUser(User* user) {
        users.push_back(user);
    }

    void addProperty(Property* property) {
        properties.push_back(property);
    }

    const std::vector<User*>& getUsers() const {
        return users;
    }

    const std::vector<Property*>& getProperties() const {
        return properties;
    }
};

void displayMenu() {
    std::cout << "\n----- Real Estate Platform Menu -----\n";
    std::cout << "1. Add Buyer\n";
    std::cout << "2. Add Seller\n";
    std::cout << "3. Add Residential Property\n";
    std::cout << "4. Add Commercial Property\n";
    std::cout << "5. Display Users\n";
    std::cout << "6. Display Properties\n";
    std::cout << "7. Buy Property\n";
    std::cout << "8. Exit\n";
    std::cout << "-------------------------------------\n";
}

int main() {
    RealEstatePlatform platform;

    int choice;
    do {
        displayMenu();
        std::cout << "Enter your choice: ";

        try {
            std::cin >> choice;

            if (!std::cin.good()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Invalid input. Please enter a number.");
            }

            switch (choice) {
                case 1: {
                    std::string username;
                    std::cout << "Enter buyer's username: ";
                    std::cin >> username;
                    platform.addUser(new Buyer(username));
                    break;
                }
                case 2: {
                    std::string username;
                    std::cout << "Enter seller's username: ";
                    std::cin >> username;
                    platform.addUser(new Seller(username));
                    break;
                }
                case 3: {
                    std::string location;
                    double price;
                    int bedrooms;
                    std::cout << "Enter property location: ";
                    std::cin >> location;
                    std::cout << "Enter property price: $";
                    std::cin >> price;
                    std::cout << "Enter number of bedrooms: ";
                    std::cin >> bedrooms;
                    platform.addProperty(new ResidentialProperty(location, price, bedrooms));
                    break;
                }
                case 4: {
                    std::string location;
                    double price;
                    std::string businessType;
                    std::cout << "Enter property location: ";
                    std::cin >> location;
                    std::cout << "Enter property price: $";
                    std::cin >> price;
                    std::cout << "Enter business type: ";
                    std::cin.ignore(); // Ignore newline character
                    std::getline(std::cin, businessType);
                    platform.addProperty(new CommercialProperty(location, price, businessType));
                    break;
                }
                case 5: {
                    const auto& users = platform.getUsers();
                    std::cout << "Users on the Platform:" << std::endl;
                    for (const auto& user : users) {
                        std::cout << "Username: " << user->getUsername() << ", Type: " << user->getUserType() << std::endl;
                    }
                    break;
                }
                case 6: {
                    const auto& properties = platform.getProperties();
                    std::cout << "Properties on the Platform:" << std::endl;
                    for (const auto& property : properties) {
                        property->display();
                    }
                    break;
                }
                case 7: {
                    int buyerIndex, propertyIndex;
                    const auto& users = platform.getUsers();
                    const auto& properties = platform.getProperties();

                    std::cout << "Buyers on the Platform:" << std::endl;
                    for (size_t i = 0; i < users.size(); ++i) {
                        if (users[i]->getUserType() == "Buyer") {
                            std::cout << i << ". " << users[i]->getUsername() << std::endl;
                        }
                    }
                    std::cout << "Enter the index of the buyer: ";
                    std::cin >> buyerIndex;

                    std::cout << "Properties on the Platform:" << std::endl;
                    for (size_t i = 0; i < properties.size(); ++i) {
                        std::cout << i << ". ";
                        properties[i]->display();
                    }
                    std::cout << "Enter the index of the property to buy: ";
                    std::cin >> propertyIndex;

                    if (buyerIndex >= 0 && buyerIndex < users.size() &&
                        propertyIndex >= 0 && propertyIndex < properties.size()) {
                        Buyer* buyer = dynamic_cast<Buyer*>(users[buyerIndex]);
                        Property* property = properties[propertyIndex];

                        if (buyer && property) {
                            buyer->buyProperty(property);
                            std::cout << "Property bought successfully!\n";

                            // Display the buyer's information, including the total bill
                            buyer->display();
                        } else {
                            std::cout << "Invalid buyer or property!\n";
                        }
                    } else {
                        std::cout << "Invalid indices!\n";
                    }
                    break;
                }
                case 8:
                    std::cout << "Exiting the program.\n";
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

    } while (choice != 8);

    return 0;
}
