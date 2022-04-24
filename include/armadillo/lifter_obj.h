class lifter_obj
{
	private:
		int dir_pin;
		int enable_pin;
		int speed_pin;
		int current_dir;
		float current_speed;

	public:
		//initialize thing
		lifter_obj(int dir_p, int enable_p, int speed_p);
		//Setting speed & direction
		void set_speed(int dir, float speed);


}