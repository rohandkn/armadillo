class lifter_obj
{
	private:
		int dir_pin;
		int enable_pin;
		int speed_pin;

		

	public:
		enum stepper_dir {cc, ccw, hold, free};
		//initialize thing
		lifter_obj(int dir_p, int enable_p, int speed_p);
		//Setting speed & direction
		void set_speed_and_dir(int dir, float speed);


};
