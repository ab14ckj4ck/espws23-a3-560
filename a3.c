//---------------------------------------------------------------------------------------------------------------------
// a3.c
//
// A card asian card game for 2 players.
//
// Group: Ingomar Mayer
//
// Author: 12232933
//---------------------------------------------------------------------------------------------------------------------
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  int number_;
  int player_;
  char color_;
} _Card_;

typedef struct CardsInHand_
{
  _Card_ card;
  struct CardsInHand_ *next;
} _CardsInHand_;

typedef struct _ChosenCards_
{
  _Card_ card;
  struct _ChosenCards_ *next;
} _ChosenCards_;

typedef struct _RowCard_
{
  _Card_ card;
  struct _RowCard_ *next;
} _RowCard_;

//---------------------------------------------------------------------------------------------------------------------
///
/// Reads a configuration file and checks if the file is in the correct format.
///
/// @param argc The number of arguments passed to the program.
/// @param argv Array of arguments passed to the program.
/// @param file Pointer to a FILE structure where the opened file will be written.
///
/// @return Returns 0 if the file is successfully read, otherwise an error code (1 - Syntax Error, 2 - Cannot open file
///         3 - Invalid file)
//
int readFile(int argc, char *argv[], FILE **file)
{
  char line[100];
  if (argc < 2 || argc > 2)
  {
    printf("Usage: ./a3 <config file>\n");
    return 1;
  }
  *file = fopen(argv[1], "r");
  if (*file == NULL)
  {
    printf("Error: Cannot open file: %s\n", argv[1]);
    return 2;
  }
  if (fgets(line, sizeof(line), *file) && strcmp(line, "ESP\n") != 0)
  {
    printf("Error: Invalid file: %s\n", argv[1]);
    return 3;
  }
  return 0;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Sorts the cards in a player's hand using the Bubble Sort algorithm.
///
/// @param hand A double pointer to the linked list of cards in a player's hand.
///
//
void bubbleSortHand(_CardsInHand_ **hand)
{
  int swapped;
  _CardsInHand_ *current;
  _CardsInHand_ *last = NULL;

  if (*hand == NULL)
  {
    return;
  }
  do
  {
    swapped = 0;
    current = *hand;

    while (current->next != last)
    {
      if (current->card.number_ > current->next->card.number_)
      {
        _Card_ temp_card = current->card;
        current->card = current->next->card;
        current->next->card = temp_card;

        swapped = 1;
      }
      current = current->next;
    }
    last = current;
  } while (swapped);
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Sorts the cards in a player's hand using the Bubble Sort algorithm.
///
/// @param chosen_cards A double pointer to the linked list of cards of a player's chosen_cards.
///
//
void bubbleSortChosen(_ChosenCards_ **chosen_cards)
{
  int swapped;
  _ChosenCards_ *current;
  _ChosenCards_ *last = NULL;

  if (*chosen_cards == NULL)
  {
    return;
  }
  do
  {
    swapped = 0;
    current = *chosen_cards;

    while (current->next != last)
    {
      if (current->card.number_ > current->next->card.number_)
      {
        _Card_ tempCard = current->card;
        current->card = current->next->card;
        current->next->card = tempCard;

        swapped = 1;
      }
      current = current->next;
    }
    last = current;
  } while (swapped);
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Adds a new card to a player's hand.
///
/// @param hand A double pointer to the linked list of cards in a player's hand.
/// @param num The number of the card to be added.
/// @param color The color character of the card to be added.
///
//
void addCardToHand(_CardsInHand_ **hand, int num, char color)
{
  _CardsInHand_ *new_node = (_CardsInHand_ *)malloc(sizeof(_CardsInHand_));
  new_node->card.number_ = num;
  new_node->card.color_ = color;
  new_node->next = NULL;
  if (*hand == NULL)
  {
    *hand = new_node;
  }
  else
  {
    _CardsInHand_ *current = *hand;
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = new_node;
  }
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Creates card instances from a file and alternately adds them to two players.
///
/// @param file A pointer to a file that contains the card information.
/// @param hand1 A pointer to a pointer to the first hand (Player 1).
/// @param hand2 A pointer to a pointer to the second hand (Player 2).
///
///
//
void createCardInstances(FILE *file, _CardsInHand_ **hand1, _CardsInHand_ **hand2)
{
  char line[100];
  int num;
  char color;
  int repeater = 0;
  int add_to_first_player = 1;

  fgets(line, sizeof(line), file);

  while (fgets(line, sizeof(line), file) && repeater < 20)
  {
    if (sscanf(line, "%d_%c", &num, &color) == 2)
    {
      if (add_to_first_player)
      {
        addCardToHand(hand1, num, color);
      }
      else
      {
        addCardToHand(hand2, num, color);
      }
      add_to_first_player = !add_to_first_player;
    }
    repeater++;
  }
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Prints the cards in a player's hand.
///
/// @param current A pointer to the linked list of cards in a player's hand.
///
/// The function iterates through the linked list and prints each card's number and color.
//
void printCardsInHand(_CardsInHand_ *current)
{
  printf("  hand cards:");
  while (current != NULL)
  {
    printf(" %d", current->card.number_);
    printf("_%c", current->card.color_);
    current = current->next;
  }
  printf("\n");
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Prints the chosen cards of a player.
///
/// @param chosenCards A pointer to the array of chosen cards.
///
//
void printChosenCards(_ChosenCards_ *current)
{
  printf("  chosen cards:");
  while (current != NULL)
  {
    printf(" %d", current->card.number_);
    printf("_%c", current->card.color_);
    current = current->next;
  }
  printf("\n");
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Prints the cards in three rows.
///
/// @param row1 A pointer to the linked list of cards in the first row.
/// @param row2 A pointer to the linked list of cards in the second row.
/// @param row3 A pointer to the linked list of cards in the third row.
///
//
void printRows(_RowCard_ *row1, _RowCard_ *row2, _RowCard_ *row3)
{
  _RowCard_ *rows[3] = {row1, row2, row3};

  for (int i = 0; i < 3; i++)
  {
    int row_counter = 0;
    _RowCard_ *current = rows[i];
    while (current != NULL)
    {
      if (row_counter == 0)
      {
        printf("  row_%d:", i + 1);
      }
      printf(" %d", current->card.number_);
      printf("_%c", current->card.color_);
      current = current->next;
      row_counter++;
    }
    if (row_counter > 0)
    {
      printf("\n");
    }
  }
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Prints the state of a player including their hand, chosen cards, and the rows.
///
/// @param row1 A pointer to the linked list of cards in the first row.
/// @param row2 A pointer to the linked list of cards in the second row.
/// @param row3 A pointer to the linked list of cards in the third row.
/// @param hand A pointer to the linked list of cards in the player's hand.
/// @param chosen A pointer to the array of the player's chosen cards.
/// @param player A string representing the player ("P1" or "P2").
///
//
void printPlayer(_RowCard_ *row1, _RowCard_ *row2, _RowCard_ *row3, _CardsInHand_ *hand, _ChosenCards_ *chosen,
                 char *player)
{
  int player_num = 0;
  if (strcmp(player, "P1") == 0)
  {
    player_num = 1;
  }
  else
  {
    player_num = 2;
  }
  printf("\nPlayer %d:\n", player_num);
  printCardsInHand(hand);
  printChosenCards(chosen);
  printRows(row1, row2, row3);
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Moves a card from a player's hand to their chosen cards.
///
/// @param hand A pointer to the current players hand.
/// @param chosen_card_player A pointer to the current players chosen cards.
/// @param chosen_card_num The number of the card to be moved from the hand to the chosen cards.
/// @return 4 if there was a memory error
/// @return 0 if the card was successfully moved
/// @return 99 if the card was not found in the hand
//
int handToChosen(_CardsInHand_ **hand, _ChosenCards_ **chosen_card_player, int chosen_card_num)
{
  _CardsInHand_ *temp = *hand;
  _CardsInHand_ *prev = NULL;

  while (temp != NULL)
  {
    if (temp->card.number_ == chosen_card_num)
    {
      _ChosenCards_ *new_node = (_ChosenCards_ *)malloc(sizeof(_ChosenCards_));
      if (new_node == NULL)
      {
        return 4;
      }
      new_node->card = temp->card;
      new_node->next = *chosen_card_player;
      *chosen_card_player = new_node;

      if (prev == NULL)
      {
        *hand = temp->next;
      }
      else
      {
        prev->next = temp->next;
      }

      free(temp);
      return 0;
    }
    prev = temp;
    temp = temp->next;
  }
  return 99;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Reads the input an returns it as a string.
///
/// @return input The input as a string.
/// @return NULL if there was a memory error
//
char *getInput()
{
  int capacity = 10;
  int input_size = 0;
  char *input = (char *)malloc(capacity * sizeof(char));
  if (input == NULL)
  {
    return NULL;
  }
  char character;
  while (1)
  {
    character = getchar();
    if (character == '\n' || character == EOF)
    {
      input[input_size] = '\0';
      break;
    }
    input[input_size] = character;
    input_size++;
    if (input_size >= capacity)
    {
      capacity *= 2;
      char *new_input = realloc(input, capacity * sizeof(char));
      if (!new_input)
      {
        free(input);
        return NULL;
      }
      input = new_input;
    }
  }
  return input;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Checks if a card is in a player's hand.
///
/// @param hand A pointer to the current players hand.
/// @param chosen_card_num The number of the card to be checked.
/// @return 0 if the card is in the hand
/// @return 50 if the card is not in the hand
//
int isCardInHand(_CardsInHand_ *hand, int chosen_card_num)
{
  while (hand != NULL)
  {
    if (hand->card.number_ == chosen_card_num)
    {
      return 0;
    }
    hand = hand->next;
  }
  return 50;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Lets the player choose a card from their hand and move it to their chosen cards.
///
/// @param hand A pointer to the current players hand.
/// @param chosen_card_player A pointer to the current players chosen cards.
/// @param player The current player "P1" or "P2".
/// @param first_second A string containing "first" or "second" to indicate which card is being chosen.
/// @return 4 if there was a memory error
/// @return 0 if the card was successfully moved
/// @return 99 if the inpu tcommand was "quit"
/// @return returncode from handToChosen
//
int choosingCards(_CardsInHand_ **hand, _ChosenCards_ **chosen_card_player, char *player, char *first_second)
{
  int returncode = 0;
  if (strcmp(first_second, "first") == 0)
  {
    printf("\n");
  }
  printf("Please choose a %s card to keep:\n", first_second);

  while (1)
  {
    printf("%s > ", player);
    char *input = getInput();
    if (input == NULL)
    {
      return 4;
    }
    for (int i = 0; input[i] != '\0'; i++)
    {
      input[i] = tolower((unsigned char)input[i]);
    }
    if (strcmp(input, "quit") == 0)
    {
      free(input);
      return 99;
    }
    char *token = strtok(input, " \n");
    int param_count = 0;
    while (token != NULL)
    {
      param_count++;
      token = strtok(NULL, " \n");
    }
    if (param_count != 1)
    {
      printf("Please enter the correct number of parameters!\n");
      free(input);
      continue;
    }
    token = strtok(input, " \n");
    int chosen_card_num = atoi(token);
    free(input);
    if (isCardInHand(*hand, chosen_card_num) == 50)
    {
      printf("Please enter the number of a card in your hand cards!\n");
      continue;
    }
    returncode = handToChosen(hand, chosen_card_player, chosen_card_num);
    if (returncode == 0)
    {
      break;
    }
  }
  return returncode;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Prints the choosing phase of a player.
///
/// @param row1 A pointer to the linked list of cards in the first row.
/// @param row2 A pointer to the linked list of cards in the second row.
/// @param row3 A pointer to the linked list of cards in the third row.
/// @param hand A pointer to the linked list of cards in the player's hand.
/// @param chosen_card_player A pointer to the linked list of cards in the player's chosen cards.
/// @param player A string representing the player ("P1" or "P2").
/// @return returncode from choosingCards
/// @return 0 to match the function type
//
int printChoosingPhase(_RowCard_ **row1, _RowCard_ **row2, _RowCard_ **row3, _CardsInHand_ **hand,
                       _ChosenCards_ **chosen_card_player, char *player)
{
  int returncode = 0;
  int card_counter = 0;
  char *num_question = "first";
  while (card_counter < 2)
  {
    bubbleSortHand(hand);
    if (card_counter == 0)
    {
      printPlayer(*row1, *row2, *row3, *hand, *chosen_card_player, player);
    }
    returncode = choosingCards(hand, chosen_card_player, player, num_question);
    if (returncode == 99 || returncode == 4)
    {
      return returncode;
    }
    card_counter++;
    num_question = "second";
  }
  return 0;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Prints the help message.
///
/// @param row1 A pointer to the linked list of cards in the first row.
/// @param row2 A pointer to the linked list of cards in the second row.
/// @param row3 A pointer to the linked list of cards in the third row.
/// @param hand A pointer to the linked list of cards in the player's hand.
/// @param chosen_card_player A pointer to the linked list of cards in the player's chosen cards.
/// @param player A string representing the player ("P1" or "P2").
//
void printHelp(_RowCard_ **row1, _RowCard_ **row2, _RowCard_ **row3, _CardsInHand_ **hand,
               _ChosenCards_ **chosen_card_player, char *player)
{
  printf("\nAvailable commands:\n\n");
  printf("- help\n  Display this help message.\n\n");
  printf("- place <row number> <card number>\n  Append a card to the chosen row or if the chosen row does not exist "
         "create it.\n\n");
  printf("- discard <card number>\n  Discard a card from the chosen cards.\n\n");
  printf("- quit\n  Terminate the program.\n\n");
  printPlayer(*row1, *row2, *row3, *hand, *chosen_card_player, player);
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Prints an error message.
///
/// @param error_msg A string containing the error message.
//
void printErrorMsg(char *error_msg)
{
  if (strcmp(error_msg, "param_count") == 0)
  {
    printf("Please enter the correct number of parameters!\n");
  }
  if (strcmp(error_msg, "wrong_cmd") == 0)
  {
    printf("Please enter a valid command!\n");
  }
  if (strcmp(error_msg, "row") == 0)
  {
    printf("Please enter a valid row number!\n");
  }
  if (strcmp(error_msg, "card_missing") == 0)
  {
    printf("Please enter the number of a card in your chosen cards!\n");
  }
  if (strcmp(error_msg, "no_fit") == 0)
  {
    printf("This card cannot extend the chosen row!\n");
  }
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Creates a copy of a string.
///
/// @param pointer to the original string
/// @return pointer to the copy of the string
/// @return NULL if there was a memory error
//
char *copyString(const char *original)
{
  if (original == NULL)
  {
    return NULL;
  }
  char *copy = (char *)malloc(strlen(original) + 1);
  if (copy == NULL)
  {
    return NULL;
  }
  strcpy(copy, original);
  return copy;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Counts the number of parameters in a string.
///
/// @param input A pointer to the string to be counted.
/// @return param_count The number of parameters in the string.
/// @return -1 if there was a memory error
//
int countParam(const char *input)
{
  int param_count = 0;
  char *input_copy = copyString(input);
  if (input_copy == NULL)
  {
    return -1; // MEM ERROR
  }
  char *token;
  char delimiter[] = " \n";
  token = strtok(input_copy, delimiter);
  while (token != NULL)
  {
    param_count++;
    token = strtok(NULL, delimiter);
  }
  free(input_copy);
  return param_count;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Extracts the row number and card number from the input string.
///
/// @param chosen_cards A pointer to the linked list of cards in the player's chosen cards.
/// @param input A pointer to the input string.
/// @param real_card A pointer to the real card number.
/// @param real_row A pointer to the real row number.
/// @return 40 if the row number is not valid
/// @return 50 if the card number is not valid
/// @return 0 if the card and row numbers are valid
/// @return 1 to fit the function type
//
int placeCardExtract(_ChosenCards_ **chosen_cards, char *input, int *real_card, int *real_row)
{
  _ChosenCards_ *current = *chosen_cards;
  int row = 0;
  int card_num = 0;
  int param_count = 0;
  char *token;
  char delimiter[] = " \n";
  token = strtok(input, delimiter);
  while (token != NULL)
  {
    if (param_count == 1)
    {
      row = atoi(token);
    }
    if (param_count == 2)
    {
      card_num = atoi(token);
    }
    token = strtok(NULL, delimiter);
    param_count++;
  }
  if (row < 1 || row > 3)
  {
    return 40;
  }
  while (current != NULL)
  {
    if (current->card.number_ == card_num)
    {
      *real_card = card_num;
      *real_row = row;
      return 0;
    }
    current = current->next;
  }

  if (current == NULL)
  {
    return 50; // Karte nicht gefunden
  }

  return 1;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Finds or creates a row.
///
/// @param row1 A pointer to the linked list of cards in the first row.
/// @param row2 A pointer to the linked list of cards in the second row.
/// @param row3 A pointer to the linked list of cards in the third row.
/// @param input_row The row number to be found or created.
/// @return target_row A pointer to the found or created row.
/// @return NULL if there was a memory error
//
_RowCard_ **findOrCreateRow(_RowCard_ **row1, _RowCard_ **row2, _RowCard_ **row3, int input_row)
{
  _RowCard_ **target_row;

  switch (input_row)
  {
  case 1:
    target_row = row1;
    break;
  case 2:
    target_row = row2;
    break;
  case 3:
    target_row = row3;
    break;
  default:
    return NULL;
  }
  if (*target_row == NULL)
  {
    *target_row = (_RowCard_ *)calloc(1, sizeof(_RowCard_));
    if (*target_row == NULL)
    {
      return NULL;
    }
    (*target_row)->next = NULL;
  }
  return target_row;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Checks if a card can be added to a row.
///
/// @param row_node A pointer to the row to be checked.
/// @param card_num The number of the card to be added.
/// @return "first" if the card can be added to the beginning of the row.
/// @return "last" if the card can be added to the end of the row.
/// @return "no_fit" if the card cannot be added to the row.
//
char *checkToAddToRow(_RowCard_ **row_node, int card_num)
{
  _RowCard_ *first = *row_node;
  _RowCard_ *last = *row_node;
  if (first->card.number_ == 0)
  {
    return "first";
  }
  while (last->next != NULL)
  {
    last = last->next;
  }
  if (first->card.number_ > card_num)
  {
    return "first";
  }
  if (last->card.number_ < card_num)
  {
    return "last";
  }
  return "no_fit";
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Removes a card from the chosen cards.
///
/// @param chosen_cards A pointer to the linked list of cards in the player's chosen cards.
/// @param card_num The number of the card to be removed.
//
void removeFromChosen(_ChosenCards_ **chosen_cards, int card_num)
{
  _ChosenCards_ *current = *chosen_cards;
  _ChosenCards_ *prev = NULL;
  while (current != NULL)
  {
    if (current->card.number_ == card_num)
    {
      if (prev == NULL)
      {
        *chosen_cards = current->next;
      }
      else
      {
        prev->next = current->next;
      }
      free(current);
      return;
    }
    prev = current;
    current = current->next;
  }
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Adds a card to a row.
///
/// @param row_node A pointer to the row to which the card is to be added.
/// @param chosen_cards A pointer to the linked list of cards in the player's chosen cards.
/// @param card_num The number of the card to be added.
/// @param add_pos Position where the card can be placed.
/// @return 4 if there was a memory error.
/// @return 50 if the card was not found in the chosen cards.
/// @return 0 if everything worked like expected.
//
int addCardToRow(_RowCard_ **row_node, _ChosenCards_ **chosen_cards, int card_num, char *add_pos)
{
  _ChosenCards_ *temp_chosen = *chosen_cards;
  while (temp_chosen != NULL && temp_chosen->card.number_ != card_num)
  {
    temp_chosen = temp_chosen->next;
  }
  if (temp_chosen == NULL)
  {
    return 50; // Karte wurde in chosen_cards nicht gefunden
  }
  if (*row_node == NULL || (*row_node)->card.number_ == 0)
  {
    if (*row_node == NULL)
    {
      *row_node = (_RowCard_ *)calloc(1, sizeof(_RowCard_));
      if (*row_node == NULL)
      {
        return 4; // Fehler bei der Speicherallokation
      }
    }
    (*row_node)->card = temp_chosen->card;
    (*row_node)->next = NULL;
  }
  else
  {
    _RowCard_ *new_node = (_RowCard_ *)calloc(1, sizeof(_RowCard_));
    if (new_node == NULL)
    {
      return 4; // Fehler bei der Speicherallokation
    }
    new_node->card = temp_chosen->card;

    if (strcmp(add_pos, "first") == 0)
    {
      new_node->next = *row_node;
      *row_node = new_node;
    }
    else if (strcmp(add_pos, "last") == 0)
    {
      _RowCard_ *current = *row_node;
      while (current->next != NULL)
      {
        current = current->next;
      }
      current->next = new_node;
    }
  }
  removeFromChosen(chosen_cards, card_num);
  return 0;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Places a card in a row.
///
/// @param row1 A pointer to the linked list of cards in the first row.
/// @param row2 A pointer to the linked list of cards in the second row.
/// @param row3 A pointer to the linked list of cards in the third row.
/// @param chosen_cards A pointer to the linked list of cards in the player's chosen cards.
/// @param input A pointer to the input string.
/// @return 99 if the card does not fit in the row.
/// @return returncode from placeCardExtract
/// @return 0 to match the function type
//
int placeCard(_RowCard_ **row1, _RowCard_ **row2, _RowCard_ **row3, _ChosenCards_ **chosen_cards, char *input)
{
  int row = 0;
  int card_num = 0;
  int returncode = 0;
  char *check_add;
  returncode = placeCardExtract(chosen_cards, input, &card_num, &row);
  if (returncode == 0)
  {
    _RowCard_ **row_node = findOrCreateRow(row1, row2, row3, row);
    check_add = checkToAddToRow(row_node, card_num);
    if (strcmp(check_add, "no_fit") == 0)
    {
      return 99; // card doesnt fit in row
    }
    addCardToRow(row_node, chosen_cards, card_num, check_add);
  }
  else
  {
    return returncode;
  }
  return 0;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Removes a card from the chosen cards.
///
/// @param chosen_cards A pointer to the linked list of cards in the player's chosen cards.
/// @param input A pointer to the input string.
/// @return 99 if the card was not found in the chosen cards.
/// @return 0 if the card was successfully removed.
//
int discardChosen(_ChosenCards_ **chosen_cards, char *input)
{
  _ChosenCards_ *current = *chosen_cards;
  _ChosenCards_ *prev = NULL;
  char *token;
  char delimiter[] = " \n";
  token = strtok(input, delimiter);
  token = strtok(NULL, delimiter);
  int chosen_card_num = atoi(token);

  while (current != NULL)
  {
    if (current->card.number_ == chosen_card_num)
    {
      if (prev == NULL)
      {
        *chosen_cards = current->next;
      }
      else
      {
        prev->next = current->next;
      }
      free(current);
      return 0;
    }
    prev = current;
    current = current->next;
  }
  return 99;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Counts how many cards are remaining in both players hands and chosen cards.
///
/// @param hand1 A pointer to the linked list of cards in the first hand.
/// @param hand2 A pointer to the linked list of cards in the second hand.
/// @param chosen1 A pointer to the linked list of cards in the first chosen cards.
/// @param chosen2 A pointer to the linked list of cards in the second chosen cards.
/// @return cards_left The number of cards remaining in both players hands and chosen cards.
//
int countHandAndChosen(_CardsInHand_ **hand1, _CardsInHand_ **hand2, _ChosenCards_ **chosen1, _ChosenCards_ **chosen2)
{
  int cards_left = 0;

  _CardsInHand_ *current_hand1 = *hand1;
  while (current_hand1 != NULL)
  {
    cards_left++;
    current_hand1 = current_hand1->next;
  }

  _CardsInHand_ *current_hand2 = *hand2;
  while (current_hand2 != NULL)
  {
    cards_left++;
    current_hand2 = current_hand2->next;
  }

  _ChosenCards_ *current_chosen1 = *chosen1;
  while (current_chosen1 != NULL)
  {
    cards_left++;
    current_chosen1 = current_chosen1->next;
  }

  _ChosenCards_ *current_chosen2 = *chosen2;
  while (current_chosen2 != NULL)
  {
    cards_left++;
    current_chosen2 = current_chosen2->next;
  }

  return cards_left;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Manages the input of the action phase.
///
/// @param row1 A pointer to the linked list of cards in the first row.
/// @param row2 A pointer to the linked list of cards in the second row.
/// @param row3 A pointer to the linked list of cards in the third row.
/// @param chosen_card_player A pointer to the linked list of cards in the player's chosen cards.
/// @param hand A pointer to the linked list of cards in the player's hand.
/// @param player A string representing the player ("P1" or "P2").
/// @param action_step A pointer to the current action step.
/// @return 4 if there was a memory error.
/// @return 99 if the input command was "quit".
/// @return 0 if everything worked like expected and the action phase of the current player is over.
//
int actionInput(_RowCard_ **row1, _RowCard_ **row2, _RowCard_ **row3, _ChosenCards_ **chosen_card_player,
                _CardsInHand_ **hand, char *player, int *action_step)
{
  char *token;
  char delimiter[] = " \n";
  char *error_msg = NULL;
  while (1)
  {
    if (error_msg != NULL)
    {
      printErrorMsg(error_msg);
    }
    printf("%s > ", player);
    char *input = getInput();
    char *input_copy = copyString(input);
    int param_count = countParam(input);
    if (input == NULL || input_copy == NULL || param_count == -1)
    {
      free(input);
      free(input_copy);
      return 4; // SEG_FAULT
    }
    token = strtok(input_copy, delimiter);
    if (token == NULL || (strcmp(token, "help") == 0 && param_count != 1) ||
        (strcmp(token, "quit") == 0 && param_count != 1) || (strcmp(token, "place") == 0 && param_count != 3) ||
        (strcmp(token, "discard") == 0 && param_count != 2))
    {
      error_msg = "param_count";
      free(input);
      free(input_copy);
      continue;
    }
    if (strcmp(token, "help") == 0)
    {
      printHelp(row1, row2, row3, hand, chosen_card_player, player);
    }
    else if (strcmp(token, "quit") == 0)
    {
      free(input);
      free(input_copy);
      return 99;
    }
    else if (strcmp(token, "place") == 0)
    {
      int returncode = placeCard(row1, row2, row3, chosen_card_player, input);
      if (returncode == 40)
      {
        error_msg = "row";
        free(input);
        free(input_copy);
        continue;
      }
      if (returncode == 50)
      {
        error_msg = "card_missing";
        free(input);
        free(input_copy);
        continue;
      }
      if (returncode == 99)
      {
        error_msg = "no_fit";
        free(input);
        free(input_copy);
        continue;
      }
      printPlayer(*row1, *row2, *row3, *hand, *chosen_card_player, player);
      if (returncode != 99)
      {
        (*action_step)++;
      }
    }
    else if (strcmp(token, "discard") == 0)
    {
      int return_discard = 0;
      return_discard = discardChosen(chosen_card_player, input);
      if (return_discard == 0)
      {
        printPlayer(*row1, *row2, *row3, *hand, *chosen_card_player, player);
        (*action_step)++;
      }
      else if (return_discard == 99)
      {
        error_msg = "card_missing";
        free(input);
        free(input_copy);
        continue;
      }
    }
    else
    {
      error_msg = "Please enter a valid command!\n";
      free(input);
      free(input_copy);
      continue;
    }
    free(input_copy);
    free(input);
    return 0;
  }
  return 0;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Prints the action phase of a player.
///
/// @param row1 A pointer to the linked list of cards in the first row.
/// @param row2 A pointer to the linked list of cards in the second row.
/// @param row3 A pointer to the linked list of cards in the third row.
/// @param chosen_card_player A pointer to the linked list of cards in the player's chosen cards.
/// @param hand A pointer to the linked list of cards in the player's hand.
/// @param player A string representing the player ("P1" or "P2").
/// @return returncode from actionInput
/// @return 0 if everything worked out.
//
int printActionPhase(_RowCard_ **row1, _RowCard_ **row2, _RowCard_ **row3, _ChosenCards_ **chosen_card_player,
                     _CardsInHand_ **hand, char *player)
{
  int action_step = 0;
  while (action_step < 2)
  {
    printf("\nWhat do you want to do?\n");
    int returncode = actionInput(row1, row2, row3, chosen_card_player, hand, player, &action_step);
    if (returncode != 0)
    {
      return returncode;
    }
  }
  return 0;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Switches the hands of the two players.
///
/// @param hand1 A pointer to the linked list of cards in the first hand.
/// @param hand2 A pointer to the linked list of cards in the second hand.
//
void switchHands(_CardsInHand_ **hand1, _CardsInHand_ **hand2)
{
  _CardsInHand_ *temp = *hand1;
  *hand1 = *hand2;
  *hand2 = temp;

  for (_CardsInHand_ *current = *hand1; current != NULL; current = current->next)
  {
    current->card.player_ = 1;
  }
  for (_CardsInHand_ *current = *hand2; current != NULL; current = current->next)
  {
    current->card.player_ = 2;
  }
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Manages the game loop.
///
/// @param row1_p1 A pointer to the linked list of cards in the first row of player 1.
/// @param row2_p1 A pointer to the linked list of cards in the second row of player 1.
/// @param row3_p1 A pointer to the linked list of cards in the third row of player 1.
/// @param row1_p2 A pointer to the linked list of cards in the first row of player 2.
/// @param row2_p2 A pointer to the linked list of cards in the second row of player 2.
/// @param row3_p2 A pointer to the linked list of cards in the third row of player 2.
/// @param hand1 A pointer to the linked list of cards in the first hand.
/// @param hand2 A pointer to the linked list of cards in the second hand.
/// @param chosen_player1 A pointer to the linked list of cards in the chosen cards of player 1.
/// @param chosen_player2 A pointer to the linked list of cards in the chosen cards of player 2.
/// @return returncode from printChoosingPhase or printActionPhase
int gameLoop(_RowCard_ **row1_p1, _RowCard_ **row2_p1, _RowCard_ **row3_p1, _RowCard_ **row1_p2, _RowCard_ **row2_p2,
             _RowCard_ **row3_p2, _CardsInHand_ **hand1, _CardsInHand_ **hand2, _ChosenCards_ **chosen_player1,
             _ChosenCards_ **chosen_player2)
{
  int returncode = 0;
  int cards_left = 1;
  printf("Welcome to SyntaxSakura (2 players are playing)!\n\n");
  while (cards_left != 0)
  {
    printf("-------------------\nCARD CHOOSING PHASE\n-------------------\n");
    returncode = printChoosingPhase(row1_p1, row2_p1, row3_p1, hand1, chosen_player1, "P1");
    if (returncode != 0)
    {
      return returncode;
    }
    returncode = printChoosingPhase(row1_p2, row2_p2, row3_p2, hand2, chosen_player2, "P2");
    if (returncode != 0)
    {
      return returncode;
    }
    printf("\nCard choosing phase is over - passing remaining hand cards to the next player!\n\n");
    switchHands(hand1, hand2);
    printf("------------\nACTION PHASE\n------------\n");
    bubbleSortHand(hand1);
    bubbleSortChosen(chosen_player1);
    printPlayer(*row1_p1, *row2_p1, *row3_p1, *hand1, *chosen_player1, "P1");
    returncode = printActionPhase(row1_p1, row2_p1, row3_p1, chosen_player1, hand1, "P1");
    if (returncode != 0)
    {
      return returncode;
    }
    bubbleSortHand(hand2);
    bubbleSortChosen(chosen_player2);
    printf("\n");
    printPlayer(*row1_p2, *row2_p2, *row3_p2, *hand2, *chosen_player2, "P2");
    returncode = printActionPhase(row1_p2, row2_p2, row3_p2, chosen_player2, hand2, "P2");
    if (returncode != 0)
    {
      return returncode;
    }
    cards_left = countHandAndChosen(hand1, hand2, chosen_player1, chosen_player2);
    printf("\n\nAction phase is over - starting next game round!\n\n");
  }
  printf("\n");
  return returncode;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Calculates the points of a player.
///
/// @param row1 A pointer to the linked list of cards in the first row.
/// @param row2 A pointer to the linked list of cards in the second row.
/// @param row3 A pointer to the linked list of cards in the third row.
/// @return points_all The total points of the player.
//
int calcPoints(_RowCard_ *row1, _RowCard_ *row2, _RowCard_ *row3)
{
  const int RED = 10;
  const int WHITE = 7;
  const int GREEN = 4;
  const int BLUE = 3;
  int points_row[3] = {0, 0, 0};
  int card_count[3] = {0, 0, 0};
  _RowCard_ *rows[3] = {row1, row2, row3};
  for (int row_num = 0; row_num < 3; row_num++)
  {
    while (rows[row_num] != NULL)
    {
      switch (rows[row_num]->card.color_)
      {
      case 'b':
        points_row[row_num] += BLUE;
        break;
      case 'g':
        points_row[row_num] += GREEN;
        break;
      case 'w':
        points_row[row_num] += WHITE;
        break;
      case 'r':
        points_row[row_num] += RED;
        break;
      }
      card_count[row_num]++;
      rows[row_num] = rows[row_num]->next;
    }
  }
  int max_cards_index = 0;
  for (int i = 1; i < 3; i++)
  {
    if (card_count[i] > card_count[max_cards_index])
    {
      max_cards_index = i;
    }
  }
  points_row[max_cards_index] *= 2;
  int points_all = points_row[0] + points_row[1] + points_row[2];
  return points_all;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Prints the points of both players and writes them to the current config file.
///
/// @param points_player1 The points of player 1.
/// @param points_player2 The points of player 2.
/// @param filename A pointer to the filename.
//
void printPoints(int points_player1, int points_player2, char *filename)
{
  FILE *file = fopen(filename, "a");
  if (file == NULL)
  {
    printf("Warning: Results not written to file!\n");
    return;
  }

  if (points_player1 < points_player2)
  {
    printf("Player 2: %d points\n", points_player2);
    printf("Player 1: %d points\n", points_player1);
    printf("\nCongratulations! Player 2 wins the game!\n");
  }
  else
  {
    printf("Player 1: %d points\n", points_player1);
    printf("Player 2: %d points\n", points_player2);
    printf("\nCongratulations! Player 1 wins the game!\n");
  }

  fseek(file, 0, SEEK_END);
  if (ftell(file) > 0)
  {
    fprintf(file, "\n");
  }

  if (points_player1 < points_player2)
  {
    fprintf(file, "Player 2: %d points\n", points_player2);
    fprintf(file, "Player 1: %d points\n", points_player1);
    fprintf(file, "\nCongratulations! Player 2 wins the game!\n");
  }
  else
  {
    fprintf(file, "Player 1: %d points\n", points_player1);
    fprintf(file, "Player 2: %d points\n", points_player2);
    fprintf(file, "\nCongratulations! Player 1 wins the game!\n");
  }

  fclose(file);
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Frees the memory of a linked list.
///
/// @param head A pointer to the head of the linked list.
//
void freeList(_RowCard_ **head)
{
  _RowCard_ *current = *head;
  while (current != NULL)
  {
    _RowCard_ *next = current->next;
    free(current);
    current = next;
  }
  *head = NULL;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Frees the memory of everything that's left.
///
/// @param hand1 A pointer to the linked list of cards in the first hand.
/// @param hand2 A pointer to the linked list of cards in the second hand.
/// @param chosen_p1 A pointer to the linked list of cards in the chosen cards of player 1.
/// @param chosen_p2 A pointer to the linked list of cards in the chosen cards of player 2.
/// @param row1_p1 A pointer to the linked list of cards in the first row of player 1.
/// @param row2_p1 A pointer to the linked list of cards in the second row of player 1.
/// @param row3_p1 A pointer to the linked list of cards in the third row of player 1.
/// @param row1_p2 A pointer to the linked list of cards in the first row of player 2.
/// @param row2_p2 A pointer to the linked list of cards in the second row of player 2.
/// @param row3_p2 A pointer to the linked list of cards in the third row of player 2.
//
void iWantToBreakFree(_CardsInHand_ **hand1, _CardsInHand_ **hand2, _ChosenCards_ **chosen_p1,
                      _ChosenCards_ **chosen_p2, _RowCard_ **row1_p1, _RowCard_ **row2_p1, _RowCard_ **row3_p1,
                      _RowCard_ **row1_p2, _RowCard_ **row2_p2, _RowCard_ **row3_p2)

{
  freeList((_RowCard_ **)hand1);
  freeList((_RowCard_ **)hand2);
  freeList((_RowCard_ **)chosen_p1);
  freeList((_RowCard_ **)chosen_p2);

  freeList(row1_p1);
  freeList(row2_p1);
  freeList(row3_p1);

  freeList(row1_p2);
  freeList(row2_p2);
  freeList(row3_p2);
}

//---------------------------------------------------------------------------------------------------------------------
///
/// Main function.
///
/// @param argc The number of arguments.
/// @param argv The arguments.
/// @return returncode from readFile
/// @return 99 if the user wants to quit
/// @return 4 if there was a memory error
/// @return 0 normal exit
//
int main(int argc, char *argv[])
{
  FILE *file;
  _CardsInHand_ *hand1 = NULL;
  _CardsInHand_ *hand2 = NULL;
  _ChosenCards_ *chosen_player1 = NULL;
  _ChosenCards_ *chosen_player2 = NULL;
  _RowCard_ *row1_p1 = NULL;
  _RowCard_ *row2_p1 = NULL;
  _RowCard_ *row3_p1 = NULL;
  _RowCard_ *row1_p2 = NULL;
  _RowCard_ *row2_p2 = NULL;
  _RowCard_ *row3_p2 = NULL;
  int return_file_open = readFile(argc, argv, &file);
  int returncode_game_loop = 0;
  int points_player1 = 0;
  int points_player2 = 0;
  if (return_file_open != 0)
  {
    return return_file_open;
  }
  createCardInstances(file, &hand1, &hand2);
  returncode_game_loop = gameLoop(&row1_p1, &row2_p1, &row3_p1, &row1_p2, &row2_p2, &row3_p2, &hand1, &hand2,
                                  &chosen_player1, &chosen_player2);
  if (returncode_game_loop == 99)
  {
    iWantToBreakFree(&hand1, &hand2, &chosen_player1, &chosen_player2, &row1_p1, &row2_p1, &row3_p1, &row1_p2, &row2_p2,
                     &row3_p2);
    fclose(file);
    return 0; // quit
  }
  else if (returncode_game_loop == 4)
  {
    fclose(file);
    return 4; // seg fault
  }
  fclose(file);
  points_player1 = calcPoints(row1_p1, row2_p1, row3_p1);
  points_player2 = calcPoints(row1_p2, row2_p2, row3_p2);
  printPoints(points_player1, points_player2, argv[1]);
  iWantToBreakFree(&hand1, &hand2, &chosen_player1, &chosen_player2, &row1_p1, &row2_p1, &row3_p1, &row1_p2, &row2_p2,
                   &row3_p2);
  return 0;
}
