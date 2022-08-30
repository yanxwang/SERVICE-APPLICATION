#include "mainwin.h"
#include "dog.h"
#include "cat.h"
#include "rabbit.h"
#include "client.h"
#include <sstream>

Mainwin::Mainwin() : shelter{new Shelter{"Mavs Animal Shelter"}} {

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_default_size(800, 600);
    set_title(APP_TITLE);

    // Put a vertical box container as the Window contents
    Gtk::Box *vbox = Gtk::manage(new Gtk::VBox);
    add(*vbox);

    // ///////
    // M E N U
    // Add a menu bar as the top item in the vertical box
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar);
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

    //     F I L E
    // Create a File menu and add to the menu bar
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

    //         Q U I T
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect([this] {this->on_quit_click();});
    filemenu->append(*menuitem_quit);

    //     A N I M A L
    // Create an Animal menu and add to the menu bar
    Gtk::MenuItem *menuitem_animal = Gtk::manage(new Gtk::MenuItem("_Animal", true));
    menubar->append(*menuitem_animal);
    Gtk::Menu *animalmenu = Gtk::manage(new Gtk::Menu());
    menuitem_animal->set_submenu(*animalmenu);

    //           N E W
    // Append New to the Animal menu
    Gtk::MenuItem *menuitem_newanimal = Gtk::manage(new Gtk::MenuItem("_New", true));
    menuitem_newanimal->signal_activate().connect([this] {this->on_new_animal_click();});
    animalmenu->append(*menuitem_newanimal);

    //           L I S T
    // Append List to the Animal menu
    Gtk::MenuItem *menuitem_listanimal = Gtk::manage(new Gtk::MenuItem("_List", true));
    menuitem_listanimal->signal_activate().connect([this] {this->on_list_animals_click();});
    animalmenu->append(*menuitem_listanimal);

    //     C L I E N T
    // Create a Client menu and add to the menu bar
    Gtk::MenuItem *menuitem_client = Gtk::manage(new Gtk::MenuItem("_Client", true));
    menubar->append(*menuitem_client);
    Gtk::Menu *clientmenu = Gtk::manage(new Gtk::Menu());
    menuitem_client->set_submenu(*clientmenu);

    //           N E W
    // Append New to the Client menu
    Gtk::MenuItem *menuitem_newclient = Gtk::manage(new Gtk::MenuItem("_New", true));
    menuitem_newclient->signal_activate().connect([this] {this->on_new_client_click();});
    clientmenu->append(*menuitem_newclient);
   
    Gtk::MenuItem *menuitem_listclient=Gtk::manage(new Gtk::MenuItem("_List",true));
    menuitem_listclient->signal_activate().connect([this]{this->on_list_client_click();});
    clientmenu->append(*menuitem_listclient);
  
    Gtk::MenuItem *menuitem_adoptAnimal=Gtk::manage(new Gtk::MenuItem("_Adopt An Animal",true));
    menuitem_adoptAnimal->signal_activate().connect([this]{this->on_adopt_animal_click();});
    clientmenu->append(*menuitem_adoptAnimal);

    // /////////////
    // T O O L B A R
    // Add a toolbar to the vertical box below the menu
    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    toolbar->override_background_color(Gdk::RGBA{"gray"});
   
    Gtk::ToolButton* exit=Gtk::manage(new Gtk::ToolButton);
    Gtk::Image image("exit.svg");
    exit->set_icon_widget(image); //<div>Icons made by <a href="https://www.flaticon.com/authors/freepik"        title="Freepik">Freepik</a> from <a href="https://www.flaticon.com/" title="Flaticon">www.flaticon.com</a></div>
    exit->signal_clicked().connect([this] {this->on_quit_click();});
    toolbar->set_icon_size(Gtk::ICON_SIZE_LARGE_TOOLBAR);
    toolbar->add(*exit);
    

    vbox->pack_start(*toolbar, Gtk::PACK_SHRINK, 0);
    
    // ///////////////////////
    // D A T A   D I S P L A Y
    // Provide a text entry box to show the remaining data
    data = Gtk::manage(new Gtk::Label());
    data->set_hexpand(true);
    data->set_vexpand(true);
    Gtk::ScrolledWindow* scroller = Gtk::manage(new Gtk::ScrolledWindow);
    scroller->add(*data);
    vbox->pack_start(*scroller, Gtk::PACK_EXPAND_WIDGET, 0);

    // ///////////////////////////////////
    // S T A T U S   B A R   D I S P L A Y
    // Provide a status bar for program messages
    msg = Gtk::manage(new Gtk::Label());
    msg->set_hexpand(true);
    msg->override_background_color(Gdk::RGBA{"gray"});
    vbox->pack_start(*msg, Gtk::PACK_SHRINK, 0);

    // Make the box and everything in it visible
    vbox->show_all();
}

Mainwin::~Mainwin() { }

// /////////////////
// C A L L B A C K S
// /////////////////

void Mainwin::on_quit_click() {
    close();
}

void Mainwin::on_new_animal_click() {

    Gtk::Dialog adialog{"Animal Type", *this};
    Gtk::ComboBoxText atype;
    atype.append("Dog");
    atype.append("Cat");
    atype.append("Rabbit");
    adialog.get_content_area()->pack_start(atype, Gtk::PACK_SHRINK, 0);
    adialog.add_button("Select", 1);
    adialog.add_button("Cancel", 0);
    adialog.show_all();
    if (adialog.run() == 0) return;

    std::string animal_type;
    Gtk::ComboBoxText c_breed;
    if (atype.get_active_row_number() == 0) {
        animal_type = "Dog";
        for(auto b : dog_breeds) c_breed.append(to_string(b));
    } else if (atype.get_active_row_number() == 1) {
        animal_type = "Cat";
        for (auto& [c, s] : cats_map) c_breed.append(to_string(c));
    } else if (atype.get_active_row_number() == 2) {
        animal_type = "Rabbit";
        for(auto r : rabbit_breeds) c_breed.append(to_string(r));
    }

    Gtk::Dialog dialog{animal_type + "Information", *this};

    Gtk::Grid grid;

    Gtk::Label l_name{"Name"};
    Gtk::Entry e_name;
    grid.attach(l_name, 0, 0, 1, 1);
    grid.attach(e_name, 1, 0, 2, 1);

    Gtk::Label l_breed{"Breed"};
    c_breed.set_active(0);
    grid.attach(l_breed, 0, 1, 1, 1);
    grid.attach(c_breed, 1, 1, 2, 1);

    Gtk::Label l_gender{"Gender"};
    Gtk::ComboBoxText c_gender;
    c_gender.append("Female");
    c_gender.append("Male");
    c_gender.set_active(0);
    grid.attach(l_gender, 0, 2, 1, 1);
    grid.attach(c_gender, 1, 2, 2, 1);

    Gtk::Label l_age{"Age"};
    Gtk::SpinButton s_age;
    s_age.set_range(0,99);
    s_age.set_increments(1,5);
    s_age.set_value(5);
    grid.attach(l_age, 0, 3, 1, 1);
    grid.attach(s_age, 1, 3, 2, 1);

    dialog.get_content_area()->add(grid);

    dialog.add_button("Add " + animal_type, 1);
    dialog.add_button("Cancel", 0);

    dialog.show_all();

    while(dialog.run()) {
        if (e_name.get_text().size() == 0) {e_name.set_text("*required*"); continue;}
        Animal* animal;
        if (animal_type == "Dog")
            animal = new Dog{dog_breeds[c_breed.get_active_row_number()], 
                             e_name.get_text(),
                             (c_gender.get_active_row_number() ? Gender::MALE : Gender::FEMALE),
                             static_cast<int>(s_age.get_value())};
        else if (animal_type == "Cat")
            animal = new Cat{cat_breeds[c_breed.get_active_row_number()], 
                             e_name.get_text(),
                             (c_gender.get_active_row_number() ? Gender::MALE : Gender::FEMALE),
                             static_cast<int>(s_age.get_value())};
        else if (animal_type == "Rabbit")
            animal = new Rabbit{rabbit_breeds[c_breed.get_active_row_number()], 
                             e_name.get_text(),
                             (c_gender.get_active_row_number() ? Gender::MALE : Gender::FEMALE),
                             static_cast<int>(s_age.get_value())};
        else
            throw std::runtime_error{"Invalid animal type: " + animal_type};
        shelter->add_animal(*animal);
        std::ostringstream oss;
        oss << "Added " << *animal;
        status(oss.str());
        break;
    }
}

void Mainwin::on_list_animals_click() {
    std::ostringstream oss;
    for(int i=0; i<shelter->num_animals(); ++i)
        oss << shelter->animal(i) << '\n'; 
    data->set_text(oss.str());
    status("");
}      // List all animals

void Mainwin::on_new_client_click() {
    Gtk::Dialog dialog{"Client Information", *this};

    Gtk::Grid grid;

    Gtk::Label l_name{"Name"};
    Gtk::Entry e_name;
    grid.attach(l_name, 0, 0, 1, 1);
    grid.attach(e_name, 1, 0, 2, 1);

    Gtk::Label l_phone{"Phone"};
    Gtk::Entry e_phone;
    grid.attach(l_phone, 0, 1, 1, 1);
    grid.attach(e_phone, 1, 1, 2, 1);

    Gtk::Label l_email{"Email"};
    Gtk::Entry e_email;
    grid.attach(l_email, 0, 2, 1, 1);
    grid.attach(e_email, 1, 2, 2, 1);

    dialog.get_content_area()->add(grid);

    dialog.add_button("Add Client", 1);
    dialog.add_button("Cancel", 0);

    dialog.show_all();

    while(dialog.run()) {
        if (e_name.get_text().size() == 0) {e_name.set_text("*required*"); continue;}
        if (e_phone.get_text().size() == 0) {e_phone.set_text("*required*"); continue;}
        if (e_email.get_text().size() == 0) {e_email.set_text("*required*"); continue;}

        shelter->add_client(*(new Client{e_name.get_text(), e_phone.get_text(), e_email.get_text()}));
        break;
    }
}
void Mainwin::on_list_client_click() {
    std::ostringstream oss;
    for(int i=0; i<shelter->num_clients(); ++i)
        oss << shelter->client(i) << '\n'; 
    data->set_text(oss.str());
    status("");
}
 void Mainwin::on_adopt_animal_click(){
  if(shelter->num_clients()>=1){
   Gtk::Dialog dialog{"Select a client",*this};
   Gtk::Grid grid;
   Gtk::ComboBoxText m_Combo;
   m_Combo.set_active(-1);
   for(int i=0;i<shelter->num_clients();i++){
  std::stringstream oss;
  oss<<shelter->client(i)<<std::endl;
   m_Combo.append(oss.str());
}
  grid.attach(m_Combo,1,2,2,1);
  dialog.get_content_area()->add(grid);
  dialog.add_button("Add Client", 1);
  dialog.add_button("Cancel", 0);
  dialog.show_all_children();
  while(dialog.run()){
 int client_choice=m_Combo.get_active_row_number();
  if(client_choice==-1){continue;}
  break;
 }
 if(shelter->num_animals()>=1){
  Gtk::Dialog dialog{"Select an animal",*this};
   Gtk::Grid grid;
   Gtk::ComboBoxText m_Combo;
   m_Combo.set_active(-1);
   for(int i=0;i<shelter->num_animals();i++){
  std::stringstream oss1;
  oss1<<shelter->animal(i)<<std::endl;
   m_Combo.append(oss1.str());
}
  grid.attach(m_Combo,1,2,2,1);
  dialog.get_content_area()->add(grid);
  dialog.add_button("Add Animal", 1);
  dialog.add_button("Cancel", 0);
  dialog.show_all_children();
  while(dialog.run()){
  int animal_choice=m_Combo.get_active_row_number();
 if(animal_choice==-1){continue;}
 break;
}
 //shelter->adopt(shelter->client(client_choice),shelter->animal(animal_choice));
}else{
 Gtk::Dialog dialog{"No animals added yet",*this};
  int i=0;
   while(dialog.run()){
   if(i<6000){i++;continue;}
  
}
   dialog.close();
}

} 
else{
   Gtk::Dialog dialog{"No clients added yet",*this};
   dialog.run();
   dialog.close();
}
}
// /////////////////
// U T I L I T I E S
// /////////////////

void Mainwin::status(std::string s) {
    msg->set_text(s);
}
