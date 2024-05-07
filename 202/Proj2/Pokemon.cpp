#include "Pokemon.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

// Name: Pokemon (default constructor)
  // Desc: Constructs an empty Pokemon
  // Preconditions - None
  // Postconditions - Pokemon created
  Pokemon::Pokemon(){
    m_num = 0; //Number of the Pokemon
    m_name = ""; //Name of the Pokemon
    m_CP = 0; //Combat power of the Pokemon
    m_rarity = 0;

  }
  // Name: Pokemon (overloaded constructor)
  // Desc: Constructs a populated Pokemon
  // Preconditions - None
  // Postconditions - Pokemon created with passed num, name, cp, rarity
  Pokemon::Pokemon(int num, string name, int cp, int rarity){
    //validate the nums, names, cp, rarity. 
    if(num > 0){
        m_num = num;
    }
    SetName(name);
    SetCP(cp);
    SetRarity(rarity);

  }
  // Name: GetCP
  // Desc: Returns CP
  // Preconditions - None
  // Postconditions - Returns CP
  int Pokemon::GetCP(){
    return m_CP;

  }
  // Name: GetRarity
  // Desc: Returns rarity
  // Preconditions - None
  // Postconditions - Returns rarity
  int Pokemon::GetRarity(){
    return m_rarity;
  }
  // Name: GetName
  // Desc: Returns name
  // Preconditions - None
  // Postconditions - Returns name
  string Pokemon::GetName(){
    return m_name;
  }
  // Name: GetNum
  // Desc: Returns num
  // Preconditions - None
  // Postconditions - Returns num
  int Pokemon::GetNum(){
    return m_num;
  };
  // Name: SetRarity
  // Desc: Updates the rarity (between 1 and 3)
  // Preconditions - None
  // Postconditions - Updates m_rarity
  void Pokemon::SetRarity(int newRarity){
    m_rarity = newRarity;
  }
  // Name: SetName
  // Desc: Updates the name
  // Preconditions - None
  // Postconditions - Updates m_name
  void Pokemon::SetName(string newName){
    m_name = newName;
  }
  // Name: SetCP
  // Desc: Updates the combat power (CP)
  // Preconditions - None
  // Postconditions - Updates m_CP
  void Pokemon::SetCP(int newCP){
    m_CP = newCP;
  }
  // Name: Train
  // Desc: Increases the CP by TRAIN_POWER up to maxCP
  // Preconditions - maxCP is calculated and passed to this function
  // Postconditions - Updates m_CP by TRAIN_POWER to maxCP
  void Pokemon::Train(int maxCP){
    if(m_CP <= maxCP){
      if(m_CP == maxCP){
        m_CP = maxCP;
      }else{
        m_CP += TRAIN_VALUE;
      }
    }
    
  }