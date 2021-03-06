// ------------------------------------------------------------------------ //
//									    //
//									    //
//				Functions for robot operations		    //
//									    //
//									    //
// ------------------------------------------------------------------------ //
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#define DEBUG 0

unsigned int shift(unsigned int position, char direction);
bool can_i_go(unsigned int position, char direction);
unsigned int go_to(unsigned int position, unsigned int destination);
bool is_next_empty(unsigned int position, char direction, char array[]);
bool array_full(char array[],unsigned int position);
unsigned int get_spot_to_place(unsigned int start, unsigned int position, char robot,char array[]);
char cascade_move(char array[], char direction, char robot, char position);

using namespace std;
//
// Function get_block
// Reads in a single character value from the keyboard
// This is the input from the chute
// Returns: a single character in uppercase
//
// Example function call: 	block = get_block();

char get_block(void)
{
	char block;
	cout << "Enter one block: ";
	cin >> block;
	return toupper(block);
}
//
// Function print_slots
// Prints the contents of the slots array in a well formatted form.
// Input: Array of slots
// Returns: Nothing (void)
//
// Example function call: print_slots(slot_array);

//Ben was here

void print_slots(char slots[])
{
	unsigned int j = 0;
	for (j = 0; j < 20; j++)
	{
		cout << setw(3) << j;
	}
	cout << endl;
	for (j = 0; j < 20; j++)
	{
		cout << setw(3) << slots[j];
	}
	cout << endl;

}

// Function put_block
// This function stores a character into the character array representing the slots
//
// Inputs:
// block - type char - The character to be inserted into a slot
// position - type unsigned int - index of the slot where the block will go
// array - type char - array of slots containing the blocks
//
// Returns:
// position - type unsigned int - the index of the slot where the block was placed
//
// Example function call: 	put_block(block, position, slots);

unsigned int put_block(char block, unsigned int position, char array[])
{
	array[position] = block;
	if (DEBUG)
		cout << "Block " << block << " inserted into slot " << position << endl;
	return position;
}

// Function remove_block
// This function removes a block from the slot array
// The slot where the block is removed is then set to a space
//
// Inputs:
// position - type unsigned int - index of the slot where block is located
// array - type char - array of slots containing the blocks
//
// Returns:
// block - type char - the block removed from the slot
//
// Example function call: 	remove_block(position, slots);

unsigned int remove_block(unsigned int position, char array[])
{
	char block = ' ';
	block = array[position];
	array[position] = ' ';  // Reset slot to blank after block removed
	if (DEBUG)
		cout << "Block " << block << " removed from slot " << position + 1 << endl;
	return block;
}


// Function shift_right
// This function increments the index simulating a movement of the robot
// to the next higher slot (index) of the array
//
// Inputs:
// position - type unsigned int - current slot position
//
// Returns:
// position - type unsigned int - The updated position which is input position + 1
//
// Example function call:  position = shift_right(position)
//

unsigned int shift_right(unsigned int position)
{
	position++;
	if (DEBUG)
		cout << "Position right shifted to " << position << endl;
	return position;
}

// Function shift_left
// This function decrements the index simulating a movement of the robot
// to the next lower slot (index) of the array
//
// Inputs:
// position - type unsigned int - current slot position
//
// Returns:
// position - type unsigned int - The updated position which is input position - 1
//
// Example function call: position = shift_left(position)
//

unsigned int shift_left(unsigned int position)
{
	position--;
	if (DEBUG)
		cout << "Position left shifted to " << position << endl;
	return position;
}

// Function robot_ltoreq_slot
// This function compares the value of the block held by the robot
// with the value of the block in a slot
//
// Inputs:
// robot - type char - value of block held by robot
// in_slot - type char - value of block in the slot
//
// Returns:
// true or false
// TRUE if block held by robot is LESS than or equal to the block in slot
// FALSE if block held by robot is GREATER than block in slot
//
// Example function call: if ( compare_blocks(robot_block, slot_block) )
//
bool robot_ltoreq_slot(char robot, char in_slot)
{
	if (DEBUG)
		cout << endl <<  "Comparing robot block " << robot << " with block in slot " << in_slot << endl;
	if (robot <= in_slot)
	{
		if (DEBUG)
			cout << "Returning true. Robot block LESS than or EQUAL to block in slot. " << endl;
		return true;
	}
	else
	{
		if (DEBUG)
			cout << "Returning false. Robot block GREATER than block in slot. " << endl;
		return false;
	}
}
// Function switch_blocks
// This function switches the block held by the robot with a block in a slot.
// After the switch the robot is holding the block removed from the slot.
//
// Inputs:
// robot - type char - The block to be inserted into a slot
// position - type unsigned int - index of the slot where the block will go
// array - type char - array of slots containing the blocks
//
// Returns:
// robot - type char. The value of the block removed from the slot.
//
// Example function call: block = switch_blocks(block,  position, array);
//

char switch_blocks(char robot, unsigned int position, char array[])
{
	char temp_hold;
	if (DEBUG)
		cout << "Switching blocks " << robot << " with " << array[position] << endl;
	temp_hold = robot;
	robot = array[position];
	array[position] = temp_hold;
	return robot;
}
// Function test_empty
// This function tests the array to determine if a slot is empty (NULL)
// or if the slot contains a blank. The slot array must be intialized to
// all NULL or all blanks (spaces) before any blocks are added.
//
// Inputs:
// position - type unsigned int - index of slot to be tested
//
// Returns:
// true or false as value o function
// TRUE if slot is empty
// FALSE if the slot contains a block
//
// Example function call: if ( test_empty(index, array) )
//
bool test_empty(unsigned int position, char array[])
{
	char blank = ' '; // Blank space
// REPLACED INITIAL IF LITERAL WITH THE FOLLOWING; DOES NOT COMPILE WHEN TESTING EQUIVELENCY WITH NULL
//	if  (array[position] == NULL || array[position] == blank)
	if (array[position] == blank)
	{
		if (DEBUG)
			cout << "Slot " << position << " empty. " << endl;
		return true;
	}
	else
	{
		if (DEBUG)
			cout << "Slot " << position << " contains a block " << endl;
		return false;
	}

}

// ------------------------------------------------------------------------ //
//																			//
//																			//
//				Functions for robot test cases								//
//																			//
//																			//
// ------------------------------------------------------------------------ //

//
// Function get_block_testcase
// Returns blocks for a given test case one at a time
// This function can be used for all five test cases.
//
// Input: Unsigned int case designating test case 1-5.
// Input: Index of letter desired 0 - 19.
// Returns: a single uppercase character
//
// Example function call: 	block = get_block_testcase(1, 0);
// Returns first letter of test case 1.

char get_block_testcase(unsigned int testcase, unsigned int index)
{
	string testcases[5] = { "AXFIUTRPQVWSEYJINYTB",
		"ABFGHIJKMOPRSTUVWXYZ",
		"ZYXWVUTSRPOKJIIHGFBA",
		"AAAAAYYYYYQQQQQXXXXX",
		"XXXAAAZZZAAYYVVVVQQQ" };

	return testcases[testcase - 1].at(index);
}


//
// Function get_block_testone
// Returns blocks for test case one one at a time
// Returns: a single character
//
// Example function call: 	block = get_block_testone();

char get_block_testone(void)
{
	static unsigned int index = 0;
	char test_case_one[21] = "AXFIUTRPQVWSEYJINYTB";
	return test_case_one[index++];
}



//
// Function get_block_testtwo
// Returns blocks for test case two one at a time
// Returns: a single character
//
// Example function call: 	block = get_block_testtwo();

char get_block_testtwo(void)
{
	static unsigned int index = 0;
	char test_case_two[21] = "ABFGHIJKMOPRSTUVWXYZ";
	return test_case_two[index++];
}

//
// Function get_block_testthree
// Returns blocks for test case three one at a time
// Returns: a single character
//
// Example function call: 	block = get_block_testthree();

char get_block_testthree(void)
{
	static unsigned int index = 0;
	char test_case_three[21] = "ZYXWVUTSRPOKJIIHGFBA";
	return test_case_three[index++];
}
//
// Function get_block_testfour
// Returns blocks for test case four one at a time
// Returns: a single character
//
// Example function call: 	block = get_block_testfour();

char get_block_testfour(void)
{
	static unsigned int index = 0;
	char test_case_four[21] = "AAAAAYYYYYQQQQQXXXXX";
	return test_case_four[index++];
}

//
// Function get_block_testfive
// Returns blocks for test case five one at a time
// Returns: a single character
//
// Example function call: 	block = get_block_testfive();

char get_block_testfive(void)
{
	static unsigned int index = 0;
	char test_case_five[21] = "XXXAAAZZZAAYYVVVVQQQ";
	return test_case_five[index++];
}

//Get Direction

char get_direction(unsigned int position, char array[]) { //returns the most efficient direction to shift in, or the only possible one

	/*//check for any spaces to the left

	int start = position;

	for(int i = 0; i < 20; i++) { //assumes shift will return position if at the end


		if(position == 0) {
			cout << "\n\nNo spaces to the left.\n\n";
			go_to(position, start);
			return 'R'; }


		position = shift(position, 'L');
		if(test_empty(position, array)) break; //test_empty says zero is position one
	}

	position = go_to(position, start);

	//check for any spaces to the right
	if(DEBUG) cout << "\n\nChecking right.\n\n";
	for(int i = 0; i < 20; i++) {

			if(position == 19) {
			if(DEBUG) cout << endl << endl << "No spaces to the right.\n\n";
			go_to(position, start);
			return 'L'; }

		position = shift(position, 'R');

		if(test_empty(position, array)) break;
	}

	position = go_to(position, start);

	if(DEBUG) cout << endl << endl << "Spaces on either side of index " << start << endl << endl;

	int left = 0; //represents the number of spots til a space on the left
	int right = 0; //same for the right side

	while(true) {

		position = shift(position, 'L');
		left++;
		if(test_empty(position, array)) break;
	}

	position = go_to(position, start);

	while(true) {
		position = shift(position, 'R');
		right++;
		if(test_empty(position, array)) break;
	}

	position = go_to(position, start);

	if(right >= left) return 'R';
	return 'L';*/

	int start = position;

	for(int i = 0; i < 20; i++) { //assumes shift will return position if at the end


		if(position == 19) {
			if(DEBUG) cout << "\n\nNo spaces to the right.\n\n";
			go_to(position, start);
			return 'L'; }


		position = shift(position, 'R');
		if(test_empty(position, array)) break;


	}

	return 'R';
}

//Misc. Low Level Functions

bool can_i_go(unsigned int position, char direction) {

	if(position == 19 && direction == 'R') return false;

	if(position == 0 && direction == 'L') return false;

	return true;
}

bool is_next_empty(unsigned int position, char direction, char array[]) { //assumes not at end, if at end it will return the state of the current slot

	bool retval = false;

	if(direction == 'R') {
		position = shift(position, 'R');
		retval = test_empty(position, array);
		position = shift(position, 'L');
	}
	else if(direction == 'L') {
		position = shift(position, 'L');
		retval = test_empty(position, array);
		position = shift(position, 'R');
	}

	return retval;

}

unsigned int shift(unsigned int position, char direction) { //returns new position or -1 if cannot move

	if(DEBUG) cout << "\nShifting " << direction << endl;

	if(!can_i_go(position, direction)) return position;

	if(direction == 'R') return shift_right(position);

	if(direction == 'L') return shift_left(position);

	if(DEBUG) cout << "\nThere has been an oof: shift function returning origincal position.i\n";

	return position;
}

bool array_full(char array[],unsigned int position)
{
	position = go_to(position,1);
	while(position != 19)
	{
		if(test_empty(position,array))
		{
			return false;
		}
		else if (!test_empty(position,array))
		{
			if(!can_i_go(position,'R'))
			{
				return true;
			}
			else if(can_i_go(position,'R'))
			{
				position = shift(position,'R');
			}
			else
			{
				cerr << "circumstantial oof" << endl;
			}
		}
		else
		{
			cerr << "circumstantial oof" << endl;
		}
	}
	return false;
}

unsigned int go_to(unsigned int position, unsigned int destination) { //returns the new position

	if(DEBUG) cout << "\nDestination = " << destination;

	do {
		position = shift(position, 'L'); }
	while(position != 0);

	while(position < destination) {
		position = shift(position, 'R'); }


	return position;
}

char cascade_move(char array[], char direction, char robot, unsigned int position)
{
	static int switches = 0;
	//direction = 'L';
	
	while(true)
	{
		if(test_empty(position,array))
		{
			put_block(robot,position,array);
			
			print_slots(array);
			return ' ';
		}
		else if(can_i_go(position,direction))
		{
			if(is_next_empty(position,direction,array))
			{
				robot = switch_blocks(robot,position,array);
				
				switches++;
				cout << endl << "Swapping blocks, number of swaps: " << switches << endl << endl;

				position = shift(position,direction);
				position = put_block(robot,position,array);
				print_slots(array);
				return ' ';
			}
			else
			{
				robot = switch_blocks(robot,position,array);
				
				switches++;
				cout << endl << "Swapping blocks, number of swaps: " << switches << endl << endl;
				
				position = shift(position,direction);
				print_slots(array);
			}
		}
		//return robot;
	}
}
unsigned int get_spot_to_place(unsigned int start, unsigned int position, char robot,char array[])
{

	position = go_to(position,start);
	//while(true)
	//{
		if(test_empty(position,array))
		{
			return position;
		}
		else if (robot_ltoreq_slot(robot,array[position]))
		{
			while(robot_ltoreq_slot(robot,array[position]))
			{
				
				if(test_empty(position, array) || !can_i_go(position, 'L')) break;
				position = shift(position,'L');
			}
		}
		else if (!robot_ltoreq_slot(robot,array[position]))
		{
			

			while(!robot_ltoreq_slot(robot,array[position]))
			{
				//cout << "\nGet Spot loop\n"; 
				if(test_empty(position, array))
				{
					return position;
				}
				else if(position == 19)
				{
						
					return position;

				//cout << "\nposition 1: " << position;

					break;
				}
				//int t;
				//cin >> t;
				position = shift(position,'R');


			}
		}

		
		//cout << endl << "position 2: " << position << endl;
		return position;
	//}
}

int main()
{
	
	
	/*char arr[20];

	for(int i = 0; i < 20; i++) arr[i] = ' ';


	arr[8] = 'H';
	arr[9] = 'I';
	arr[10] = 'J';
	arr[11] = 'K';
	arr[12] = 'M';

	print_slots(arr);

	unsigned int position = 7;

	//cascade_move(arr, 'R', 'L',position);
	cout << endl << "\n" << get_spot_to_place(7,'L',arr) << endl;

	print_slots(arr);

	//return 0;
	*/
	
	unsigned int position = 0;
	unsigned int start = 0;
	
	cout <<"Enter starting position: ";
	cin >> start;

	char arr[19];
	char robot = ' ';

	for(int  i = 0; i < 20; i++) {

		arr[i] = ' ';
	}


	for(int i =0; i < 20; i++) {


		
		robot = get_block_testone();
		
		if(DEBUG) cout << "block = " << robot;
		
		//cin >> temp;

		cout << "\nPlacing " << robot << " at "<< get_spot_to_place(start, position,robot,arr) << endl;
		
		if(DEBUG) cout << endl <<"ran get spot to place" << endl;

		position = go_to(position, get_spot_to_place(start, position, robot, arr));

		if(get_direction(position, arr) == 'L' && robot_ltoreq_slot(robot,arr[position])) {
			
			position = shift(position, 'L'); 
			if(robot_ltoreq_slot(robot,arr[position])) {

				position = shift(position, 'R');
			}
			else if(DEBUG) cout << endl << "Doing error correction!" << endl;
		}

		if(get_direction(position, arr) == 'R' && !robot_ltoreq_slot(robot,arr[position])) {

			position = shift(position, 'R');
			if(!robot_ltoreq_slot(robot,arr[position])) {
				position = shift(position, 'L'); }
			else {
				if(DEBUG) cout << endl << "Doing error correction!" << endl; }
		}

		cascade_move(arr, get_direction(position, arr), robot, position);
	}


	return 0;
}
