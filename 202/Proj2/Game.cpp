#include "Game.h"
#include "Pokemon.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;


 // Name: Game Constructor
  // Desc - Sets m_filename based on string passed
  // Preconditions - Input file passed
  // Postconditions - m_filename updated
  Game::Game(string filename){
      m_filename = filename;
  }
  
  // Name: LoadFile
  // Desc - Opens file and reads in each Pokemon into m_PokeDex
  // Preconditions - Input file passed and populated with Pokemon
  // Postconditions - m_pokeDex populated with Pokemon
  void Game::LoadFile(string filename){
    int pokeNum = 0;
    string pokeName = "";
    int pokeCP = 0;
    int rarity = 0;

    ifstream inputStream;
    
    inputStream.open(filename);

    while(inputStream >> pokeNum >> pokeName >> pokeCP >> rarity){
        //Pokemon myPokemons;
        Pokemon myPokemons(pokeNum,pokeName,pokeCP,rarity);
        m_pokeDex[pokeNum-1] = myPokemons; 
    }

  }
  
  // Name: DisplayPokeDex
  // Desc - Display all Pokemon in the m_pokeDex
  // Preconditions - m_pokeDex populated with Pokemon
  // Postconditions - None
  void Game::DisplayPokeDex(){
    for(int i = 1; i <= TOTAL_POKEMON; i++){
        Pokemon currPokemon = m_pokeDex[i-1];
        cout << setw(NUM_WIDTH) << i << ".   " << setw(NAME_WIDTH) << currPokemon.GetName() << endl;
    }

  }

  // Name: MainMenu
  // Desc - Displays main menu
  // Preconditions - m_pokeDex populated
  // Postconditions - Keeps calling until quit chosen
  void Game::MainMenu(){
    int user_input = 0;
    cout << "\nWhat would you like to do?:"
            "\n1. Display Complete PokeDex"
            "\n2. Display your Team"
            "\n3. Search for a new Pokemon"
            "\n4. Battle your Pokemon"
            "\n5. Train your Pokemon"
            "\n6. Exit" << endl;
            cin >> user_input;

    while(user_input != NUM_WIDTH){
          switch(user_input){
          case 1:
            DisplayPokeDex();
            break;
          case 2:
            DisplayTeam();
            break;
          case 3:
            CatchPokemon();
            break;
          case 4:
            BattlePokemon();
            break;
          case 5:
            TrainPokemon();
            break;
          case 6:
            break;
            // code block
        }
        cout << "\nWhat would you like to do?:"
                "\n1. Display Complete PokeDex"
                "\n2. Display your Team"
                "\n3. Search for a new Pokemon"
                "\n4. Battle your Pokemon"
                "\n5. Train your Pokemon"
                "\n6. Exit" << endl;
              cin >> user_input;
    }

  }
  // Name: CatchPokemon
  // Desc - Main function for catching pokemon. Does the following:
  //        1. Calls CatchMenu and stores rarity chosen
  //        2. Randomly chooses a number between 0 - 99
  //        3. If random number is less than rarity, calls FoundPokemon
  //        4. If random number is greater than rarity, indicates none found
  //        5. Call AddPokemon if new Pokemon is caught
  // Preconditions - m_pokeDex has maximum CP for Pokemon
  // Postconditions - After random Pokemon of that rarity is chosen,
  //                  this function reduces the CP of between 30-50%
  //                  and adds to m_team
  void Game::CatchPokemon(){
    cout << "it's coming here" << endl;
    int rarity = CatchMenu();
    //int rarityIndex[3] = {COMMON, UNCOMMON, ULTRA};  //1,2,3

// const int COMMON = 45; //Less than this to find a common Pokemon - 45%
// const int UNCOMMON = 25; //Less than this to find an uncommon Pokemon 25%
// const int ULTRA = 1; //Less than this to find an ultra rare Pokemon 1%
    int randomVal = 0;
    int MAX = 99;
    int MIN = 0;
    int compareVal = 0;
    
    srand(time(NULL));  //seed the random number 
    randomVal = rand() %  (MAX - MIN + 1) + MIN;
   
    if(rarity == 1){
      compareVal = COMMON;
    }else if(rarity == 2){
      compareVal = UNCOMMON;
    }else if(rarity == 3){
      compareVal = ULTRA;
    }

    cout << "randomVal: " << randomVal << "rarity: " << compareVal<< endl;

    if(randomVal <= compareVal){
      Pokemon testPokemon = FoundPokemon(rarity);
      cout << "cp chosen: " << testPokemon.GetCP()<< endl;
      AddPokemon(testPokemon);
    }else if(randomVal > compareVal){
      cout << "No Pokemon Found" << endl;
    }

  }
  // Name: CatchMenu
  // Desc - User chooses which rarity of Pokemon to try and catch
  // Preconditions - m_pokeDex has rarities of 1-3
  // Postconditions - Returns choice of 1-3
  int Game:: CatchMenu(){
    int user_input = 0;
  
    cout << "What rarity of Pokemon would you like catch?:"
            "\n1. Common (High Probability)"
            "\n2. Uncommon (Normal Probability)"
            "\n3. Ultra Rare (Extremely Low Probability)" << endl;
    cin >> user_input;

    switch(user_input){
      case 1:
        return user_input;
      case 2:
        return user_input;
      case 3:
        return user_input;
      default:
        cout << "What rarity of Pokemon would you like catch?:"
              "\n1. Common (High Probability)"
              "\n2. Uncommon (Normal Probability)"
              "\n3. Ultra Rare (Extremely Low Probability)" << endl;
        cin >> user_input;
    }
    return user_input;
  }
  // Name: FoundPokemon
  // Desc - Based on rarity passed in, randomly chooses one Pokemon
  //        from the m_pokeDex, updates the CP, and adds to m_team
  // Preconditions - m_pokeDex has maximum CP for Pokemon
  // Postconditions - After random Pokemon of that rarity is chosen,
  //                  this function reduces the CP of between 30-50%
  //                  and adds to m_team
  Pokemon Game::FoundPokemon(int rarity){
    int rarityCount = 0;  //used to count the amount of occurence for rarity.
    int index = 0;
    int randPokeIndex = 0;
    int randCP = 0;
    double convertedCP = 0;
    int arrayIndex = 0;
    Pokemon tempPokemon;
    Pokemon thisPokemon;
   
    
    //search through the pokedex and get the count of user's rarity. to be used to randomize an array of rarity.
    //used to declare and array of pokemon witht he same rarity.
    for(int i = 0; i < TOTAL_POKEMON; i++){
      Pokemon pokemon = m_pokeDex[i];
      if(pokemon.GetRarity() == rarity){
        rarityCount += 1;
      }
    }

    //create an array of same rarity
    Pokemon pokeArray[rarityCount];

    //add all the same rarity pokemon to pokeArray
    for(int i = 0; i < TOTAL_POKEMON; i++){
       tempPokemon = m_pokeDex[i];
      if(tempPokemon.GetRarity() == rarity){
        //populate pokeArray
          pokeArray[arrayIndex] = tempPokemon;
          arrayIndex++;
      }
    }

    srand(time(NULL));
    //randomVal = rand() %  MAX - MIN + 1) + MIN;
    randPokeIndex = rand() % rarityCount;

    //GET THE RANDOM PERCENTAGE TO BE USED TO REDUCED CP.
    srand(time(NULL));
    //randomVal = rand() %  MAX - MIN + 1) + MIN;
    randCP = rand() % (MAX_FIND - MIN_FIND + 1)+ MIN_FIND;
    cout << "randvalue: 30-50: " << randCP << endl;

  //look up the random pokemon and edit the cp by 30-50 %;
    
    index = FindPokemon(pokeArray[randPokeIndex].GetName());

    if(index != -1){
      thisPokemon = m_pokeDex[index];
      cout << "unchanged cp: " << thisPokemon.GetCP() << endl;
      convertedCP = thisPokemon.GetCP() - (randCP/100.00) * thisPokemon.GetCP();
      cout << "converted: " << convertedCP << endl;
      thisPokemon.SetCP(int(convertedCP));
      cout << "changed cp: " << thisPokemon.GetCP() << endl;
    } else {
      cout << "No index found" << endl;
    }

    // return pokemon so it can be added to m_team
    return thisPokemon;
  }

  // Name: AddPokemon
  // Desc - Figures out where to insert newly found Pokemon
  //        If m_team has opening, inserts into first open slot
  //        If m_team is full, inserts into first slot with lower CP
  //        If m_team is full, and new Pokemon has lower CP, does not insert
  //        Tells user if not inserted
  // Preconditions - None
  // Postconditions - New Pokemon is added to m_team if possible
  //                  or user is notified that there is no room
  void Game::AddPokemon(Pokemon newPokemon){
    //bool hasLowerCP = false;
    int i = 0; // Initialize loop counter
    bool inserted = false;// Flag to track whether insertion is done

    //check how many
    int numPokeCount = TeamSize();

  // If m_team is full, and new Pokemon has lower CP, does not insert
  // Tells user if not inserted

  // If m_team has opening, inserts into first open slot
  if(numPokeCount >= 0 && numPokeCount < 4) {
    // Add the new Pokemon to the empty slot
    if(numPokeCount == 0){
      m_team[numPokeCount] = newPokemon;
    }else {
      m_team[numPokeCount] = newPokemon;
    }
    }else if (numPokeCount == NUM_TEAM) {
    while (i < NUM_TEAM && !inserted) { // Loop until insertion is done or all slots are checked
        if (newPokemon.GetCP() > m_team[i].GetCP()) {
            cout << m_team[i].GetCP() << " 2, " << newPokemon.GetCP() << endl;
            m_team[i] = newPokemon;
            //hasLowerCP = true;
            inserted = true; // Set the flag indicating insertion
        } else {
            i++;
        }
    }
    if (!inserted) { // Check the flag to see if insertion happened
        cout << "No Pokemon Added" << endl;
    }
}
}
  // Name: TeamSize
  // Desc - Iterates through m_team to see how many team members exist
  // Preconditions - m_team exists
  // Postconditions - Returns 0 if empty otherwise up to 4
  int Game::TeamSize(){
    int teamNum = 0;
    for(int i = 0; i < NUM_TEAM; i++){
      if(m_team[i].GetName() != ""){
        teamNum += 1;
        //cout << "Tam" << teamNum << endl;
      } else {
        teamNum += 0;
      }
    }
    return teamNum;
  }
  // Name: DisplayTeam
  // Desc - Iterates through m_team to display information about team
  // Preconditions - m_team exists
  // Postconditions - None
  void Game::DisplayTeam(){
    int teamSize = TeamSize();
    if (teamSize > 0) {
        for (int i = 0; i < teamSize; i++) {
            Pokemon currPokemon = m_team[i];
            cout << i+1 << "." << setw(NAME_WIDTH) << currPokemon.GetName() << setw(NUM_WIDTH) << currPokemon.GetCP()<< endl;
        }
    } else if(teamSize == 0){
        cout << "You have no team yet. Maybe search for a Pokemon?!" << endl;
    }
}
  // Name: FindPokemon
  // Desc - Iterates through m_pokeDex to see if matching name exists
  //        Returns index if found else -1
  // Preconditions - m_pokeDex exists
  // Postconditions - Returns index of match, else -1
  int Game::FindPokemon(string name){
     for(int i = 0; i <= TOTAL_POKEMON; i++){
      Pokemon currPokemon = m_pokeDex[i];
      if(currPokemon.GetName() == name){
        return i;
      }
    }
    return -1;
  }
  // Name: TrainPokemon
  // Desc - If m_team size is 0. If 0, tells user and returns to main menu
  //        If m_team size > 0, displays team (DisplayTeam)
  //        Asks user to chose one team member
  //        Calls Train on chosen team member and passes corresponding CP
  //             value from m_pokeDex (m_pokeDex holds MA CP for all)
  // Preconditions - m_team and m_pokeDex exists
  // Postconditions - Calls Train on chosen team member
  void Game::TrainPokemon(){
    int teamSize = TeamSize();  //Returns 0 if empty otherwise up to 4
    int user_choice = 0;
    
    if(teamSize == 0){
      cout << "You have no team yet. Maybe search for a Pokemon?!" << endl;
    }else if(teamSize > 0){
      DisplayTeam(); 
      cout << "Which of your pokemon would you like to use?: " << endl;
      cin >> user_choice;
      while(user_choice > teamSize && user_choice < 0){
        cout << "Which of your pokemon would you like to use?: " << endl;
        cin >> user_choice;
      }

      int maxCPIndex = FindPokemon(m_team[user_choice-1].GetName());
      int maxCP = m_pokeDex[maxCPIndex].GetCP();
      if(teamSize != 0){
        m_team[user_choice-1].Train(maxCP);
      }
    }
  }

  // Name: BattlePokemon
  // Desc - If m_team size is 0. If 0, tells user and returns to main menu
  //        If m_team size > 0, randomly chooses Pokemon to fight from
  //        m_pokeDex. Asks which team member to use in battle.
  //        Random enemy has a CP of 0 - MAxCP + 200.
  //        Compares CP for random enemy and team member.
  //        If team member wins, indicates and returns to main menu
  //        If team member loses, indicates, sets CP to 0, returns to menu
  // Preconditions - m_team exists
  // Postconditions - Either the player wins or team member's CP is set to 0
  void Game::BattlePokemon(){
    int max = TOTAL_POKEMON;
    int min = 0;
    int randVal = 0;
    int randCP = 0;
    int teamSize = TeamSize();
    int user_choice = 0;
    if(teamSize == 0){
      cout << "You have no team yet. Maybe search for a Pokemon?!" << endl;
    }else if(teamSize > 0){
      srand(time(NULL));
      //randomVal = rand() %  MAX - MIN + 1) + MIN;
      randVal = rand() % (max- min + 1)+ min;

      Pokemon enemyPokemon = m_pokeDex[randVal];
      srand(time(NULL));
      //randomVal = rand() %  MAX - MIN + 1) + MIN;
      randCP = rand() % (enemyPokemon.GetCP() - min + 1)+ min;
      enemyPokemon.SetCP(randCP + 200);

      cout << "The enemy's Pokemon is: " << enemyPokemon.GetCP() << endl;
      cout << "Which of your pokemon would you like to use?: " << endl;
      //DisplayTeam();
      cin >> user_choice;
      while(user_choice > teamSize){
        cout << "Which of your pokemon would you like to use?: " << endl;
        cin >> user_choice;
    }

  //Compares CP for random enemy and team member.
  //If team member wins, indicates and returns to main menu
  //If team member loses, indicates, sets CP to 0, returns to menu
    if(enemyPokemon.GetCP() < m_team[user_choice-1].GetCP()){
       cout << "You won!!" << endl;
    }else{
      m_team[user_choice-1].SetCP(0);
      cout << "Cp:" << m_team[user_choice-1].GetCP() << endl;
      cout << "You lost" << endl;
      cout << "Your " << m_team[user_choice-1].GetName() << " can't lift its head" 
              "\nYou should replace it" << endl;
    }
    }
  }
  // Name: Start
  // Desc - Calls LoadFile then MainMenu
  // Preconditions - m_fileName is populated
  // Postconditions - Exits game when done running
  void Game::Start(){
    string filename = "proj2_pokeDex.txt";
    LoadFile(filename);
    MainMenu();
  }
 