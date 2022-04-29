class driver_obj
{
	private:
		int dir_pin;
		int clk_pin;
		int enable_pin;
		int current_dir = 2;
		float current_speed = -1;
		void pulse_clk(int pulses);

	public:
 		enum wheel_dir {cw = 0, ccw = 1, stop = 2};
		//initialize thing
		driver_obj(int dir_p, int clk_p, int en_p);
		//Setting speed & direction
		void set_dir(int dir, int speed);
		void set_speed(float speed);


};
