class driver_obj
{
	private:
		int dir_pin;
		int clk_pin;
		int current_dir = -1;
		float current_speed = -1;
		void pulse_clk(int pulses);

	public:
 		enum wheel_dir {cw = 0, ccw = 1, stop = 2};
		//initialize thing
		driver_obj(int dir_p, int clk_p);
		//Setting speed & direction
		void set_dir(int dir);


};
