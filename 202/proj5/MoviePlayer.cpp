//Name: MoviePlayer.cpp
//Project: CMSC 202 Project 3, Spring 2024
//Author:  Adam Owolabi
//Date:    5/02/2024
//Desc: This file implements the MoviePlayer.h file details for the class
//      The movieplayer.h/MoviePlayer.cpp are the driver class for this project.

#include "MoviePlayer.h"


using namespace std;

//const int MIN_YEAR = 1980; //Earliest year of movies in input file
//const int MAX_YEAR = 2020; //Latest year of movies in input file

//Name: MoviePlayer - Default Constructor
  //Precondition: None
  //Postcondition: Creates a new MoviePlayer with m_filename of "proj5_movies.txt"
  MoviePlayer::MoviePlayer(){
    m_filename = "proj5_movies.txt";
    //m_movieCatalog.resize(0);
    //m_playList.resize(0);
  }

  //Name: MoviePlayer - Overloaded Constructor
  //Precondition: None
  //Postcondition: Creates a new MoviePlayer with passed filename
   MoviePlayer::MoviePlayer(string filename){
    m_filename = filename;

  }

  //Name: ~MoviePlayer - Destructor
  //Precondition: None
  //Postcondition: Deallocates movies from m_movieCatalog
   MoviePlayer::~MoviePlayer(){
    for(unsigned int i = 0; i < m_movieCatalog.size(); ++i){
        Movie* thisMovie = m_movieCatalog.at(i);
        if(thisMovie != nullptr){
           delete thisMovie;
           thisMovie = nullptr;
        } 
    }
    m_movieCatalog.resize(0);

    // if(int(m_playList.GetSize()) != 0){
    //     for(int i = 0; i < m_playList.GetSize(); i++){
    //         Movie* thisMovie = m_playList.At(i);
    //         if(thisMovie != nullptr){
    //             delete thisMovie;
    //             thisMovie = nullptr;
    //         }
    //     }
    // }
    //m_playList.resize(0); 
  }

  //Name: LoadCatalog()
  //Precondition: Requires m_filename to be populated
  //Postcondition: Dynamically allocates each movie and inserts into m_movieCatalog
  //Hint:          Allowed to use stoi (string to integer) if needed
  //Hint:          Allowed to use stoul (string to long) if needed
  void  MoviePlayer::LoadCatalog(){
    char delimiter = ';';
    int i = 0;
    string title = "";
    string rating = "";
    string genre = "";
    string yearStr = ""; 
    string director = "";
    string star = "";
    string budgetStr = "";
    string grossStr = "";
    string studio = "";
    string runtimeStr = "";
    
    ifstream inputStream;
    inputStream.open(m_filename);
    if(m_filename != ""){
        //The Shining;R;Drama;1980;Stanley Kubrick;Jack Nicholson;19000000;46998772;Warner Bros.;146
        
       

        while(getline(inputStream, title, delimiter) && getline(inputStream, rating, delimiter) && getline(inputStream, genre, delimiter) && getline(inputStream, yearStr, delimiter) && getline(inputStream, director, delimiter) && getline(inputStream, star, delimiter) && getline(inputStream, budgetStr, delimiter) && getline(inputStream, grossStr, delimiter) && getline(inputStream, studio, delimiter) && getline(inputStream, runtimeStr)){
            //check if studio is 
            int year = stoi(yearStr);
            int runtime = stoi(runtimeStr);
            long budget = stoul(budgetStr);
            long gross = stoul(grossStr);

            //must check to make sure we don't have a emty studio;

            Movie *thisMovie = new Movie(title,rating,genre,year,director,star,budget,gross,studio,runtime);
            m_movieCatalog.push_back(thisMovie);
            i++;
        }
    }

    inputStream.close(); 
    cout << i << " movie files loaded." << endl;
  }

  //Name: MainMenu
  //Precondition: None
  //Postcondition: Manages the menu
  void  MoviePlayer::MainMenu(){ 
    int user_input = 0;
    int quit = 5;
    //int decision = 0;
    //StartGame();
    cout << "\nWhat would you like to do?:"
            "\n1. Display Movies by Type and Year"
            "\n2. Add Movie to Playlist"
            "\n3. Display Playlis"
            "\n4. Sort Playlist by Year"
            "\n5. Quit"
             << endl;
            cin >> user_input;
    //handles user's menu option 
    while(user_input != quit){
          switch(user_input){
          case 1:
            DisplayMovie();
            break;
          case 2:
            AddMovie();
            break;
          case 3:
            DisplayPlaylist();
            break;
          case 4:
            SortPlaylist();
            break;
            // code block
        }
       cout << "\nWhat would you like to do?:"
            "\n1. Display Movies by Type and Year"
            "\n2. Add Movie to Playlist"
            "\n3. Display Playlist"
            "\n4. Sort Playlist by Year"
            "\n5. Quit"
             << endl;
        cin >> user_input;
  }
}

  //Name: DisplayMovie
  //Desc: Asks user for year (between min and max year)
  //      Asks user for genre (no validation)
  //      Displays all movies with year and genre with location in vector
  //      Uses iterators
  //Precondition: m_movieCatalog, MIN_YEAR, and MAX_YEAR are all populated
  //Postcondition: Returns count of movies found matching year and genre else 0
  //Hint: Allowed to use ** if necessary
  int MoviePlayer::DisplayMovie(){
    string user_input = "";
    int input = 0;
    int counter = 0;
    int moviesAmount = 0;
    string genre = ""; 
    cout << "Which year would you like to display? (" << MIN_YEAR <<"-"<< MAX_YEAR<< ")" << endl;
    //cin << user_input;
    cin >> input;
    while(input < MIN_YEAR || input > MAX_YEAR){
      cout << "Which year would you like to display? (" << MIN_YEAR <<"-"<< MAX_YEAR<< ")" << endl;
      cin >> input;
    }
    cout << "******" << input << "******" << endl;
    cout << "Which genre would you like?" << endl;
    cin >> genre;
    cout << "******" << genre << "******" << endl;

  
    for(vector<Movie*>::iterator it = m_movieCatalog.begin(); it != m_movieCatalog.end(); ++it){
        counter++;
        if((*it)->GetYear() == input && (*it)->GetGenre() == genre){
            moviesAmount++;
            //3124 Wallace & Gromit: The Curse of the Were-Rabbit by Steve Box from 2005
           cout << counter << " ";
           cout << **it;
           cout << endl;
        }
    }
    counter = 0;
    cout << moviesAmount << " movies found." << endl;
    return moviesAmount;

  }
  

  //Name: AddMovie
  //Desc: Calls DisplayMovie where user chooses year and genre
  //      User enters index of movie to choose
  //      Validates for number to be between 0 - m_movieCatalog size
  //      Does NOT validate that movie chosen was from year and genre
  //      Uses overloaded << operator to display the example below
  //Example: Airplane! by Jim Abrahams from 1980 added to the playlist
  //Precondition: m_movieCatalog is populated
  //Postcondition: Adds pointer from m_catalog and inserts into m_playList
  void  MoviePlayer::AddMovie(){
    int countMovies = 0;
    int movieIndex = 0;

    

    if(m_playList.GetSize() >= 0){
      if(m_playList.GetSize() > 0){
         DisplayPlaylist();
      }
      countMovies = DisplayMovie();
      

      //display all the movies from the playlist 
      //if count > 0;
      //0 - movie_catalog size 
      //exit

    if(countMovies > 0){

      cout << "Choose the movie you would like to add: "<< endl;
      cin >> movieIndex;

      m_playList.PushBack(m_movieCatalog.at(movieIndex-1));
      cout << *(m_movieCatalog.at(movieIndex-1)) << " has been added" << endl;

     }
    }else{
      cout << "The Playlist is currently empty. " << endl;
      cout << "Choose the movie you would like to add to the playlist. " << endl;
      DisplayMovie();
    }
  }

  //Name: DisplayPlaylist
  //Precondition: None (will indicate if list is empty)
  //Postcondition: Displays the playlist using the overloaded << operator
  void  MoviePlayer::DisplayPlaylist(){
    if(m_playList.GetSize() != 0){
        for(int i = 0; i < m_playList.GetSize(); i++){
        Movie *curr = m_playList.At(i);
        cout << i+1 << ".";
        cout << *curr;  //still priting memory address
        cout << endl;
        }
    }else {
        cout << "The playlist is currently empty." << endl;
    }
  }

  //Name: SortPlaylist
  //Precondition: None (will indicate if list is empty)
  //Postcondition: Sorts the playlist by year
  void  MoviePlayer::SortPlaylist(){
    if(m_playList.GetSize() == 0){
      cout << "There are no movies to sort. maybe add some movies to playlist" << endl;
    }else{
      m_playList.Sort();
      cout << "Done sorting by year" << endl;
      cout << m_playList.GetSize() << " items sorted" << endl;
    }
    
    return;
  }

  //Name: StartPlayer
  //Precondition: None (file name has already been provided)
  //Postcondition: Loads file and calls main menu
  void  MoviePlayer::StartPlayer(){
    LoadCatalog();
    MainMenu();

  }

  //OPTIONAL: EXTRA CREDIT
  //Name: SearchMovie
  //See project document for details - must complete and submit base project first