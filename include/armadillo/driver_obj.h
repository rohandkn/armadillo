class driver_obj
{
	private:
		int dir_pin;
		int clk_pin;
		int current_dir;
		float current_speed;
		enum wheel_dir {cw, ccw, stop};
		void pulse_clk(int pulses);

	public:
		//initialize thing
		driver_obj(int dir_p, int clk_p);
		//Setting speed & direction
		void set_dir(int dir);


};
