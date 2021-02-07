#include "main.h"

using namespace pros;
bool very_useful_boolean_variable_for_rumbling = false;
bool done_auto = false;
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {

}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */void autonomous() {
 done_auto = true;

	Motor lift(15);
	Motor lift2(3);
	Motor left_mtr(1);
	Motor right_mtr(11);
	Motor left_back(6);
	Motor right_back(16);

	lift = 127;
	lift2 = 127;
	delay(2000);
	lift = 0;
	lift2 = 0;
	//left_mtr = 127;
	//left_back = 127;
	//right_mtr = -127;
	//right_back = -127;
	//delay(500);
	//left_mtr = 127;
	//left_back = 127;
	//right_mtr = 127;
	//right_back = 127;
	//delay(900);
	//left_mtr = 0;
	//left_back = 0;
	//right_mtr = 0;
	//right_back = 0;
}



int clamp(int n){
    return std::min(std::max(-127,n),127);
}
int zone(int n){
	if(abs(n)<=20){
	   return 0;
	}else{
	   return n;
	}
}

void myRumble(void* control){
  printf("Started myRumble\n");
	Controller* control_pog = (Controller*)control;
	while(true){
		if(very_useful_boolean_variable_for_rumbling){
			(*control_pog).rumble("-");
			very_useful_boolean_variable_for_rumbling = false;
			delay(500);
		}
	}
}

void opcontrol() {
	Controller master(E_CONTROLLER_MASTER);
	Task my_task(myRumble, (void*)&master, "Rumble!");

	Motor lift(15);
	Motor lift2(3);
	Motor left_mtr(1);
	Motor right_mtr(11);
	Motor left_back(6);
	Motor right_back(16);
	int liftup;

	while (true){
	   int forward = -master.get_analog(ANALOG_LEFT_X);
	   int side = -master.get_analog(ANALOG_LEFT_Y);
	   int turn = zone(master.get_analog(ANALOG_RIGHT_X));

		 if(master.get_digital(DIGITAL_A)){
			 very_useful_boolean_variable_for_rumbling = true;
			 if(master.get_digital(DIGITAL_R1)){
				 lift2 = 127;
			   lift = -127;
			 }else if(master.get_digital(DIGITAL_R2)){
				 lift2 = -127;
			   lift = 127;
			 }else{
				 lift = 0;
				 lift2 = 0;
			 }
		 }else{
			 liftup = 127 * master.get_digital(DIGITAL_R1) -127 * master.get_digital(DIGITAL_R2);

			 lift2 = liftup;
		   lift = liftup;
		 }
			 //int liftup = 127 * master.get_digital(DIGITAL_A) -127 * master.get_digital(DIGITAL_R1);



	   left_mtr = -0.95 * clamp((forward+side-2*turn)/(1+abs(turn)/127.0));
	   right_mtr = -0.95 * clamp((forward-side-2*turn)/(1+abs(turn)/127.0));
	   left_back = 0.95 * clamp((forward-side+2*turn)/(1+abs(turn)/127.0));
	   right_back = 0.95 * clamp((forward+side+2*turn)/(1+abs(turn)/127.0));
		 delay(20);
	 }
 }
