// Function used by InputKey
int getCharWithoutEnter()
{
	int c = 0;
	struct termios org_opts, new_opts;
	int res = 0;

	// store old settings
	res = tcgetattr(STDIN_FILENO, &org_opts);
	assert(res == 0);
	
	// set new terminal parms
	memcpy(&new_opts, &org_opts, sizeof(new_opts));
	new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL
						  | ECHOPRT | ECHOKE | ICRNL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
	c = getchar();
	
	// restore old settings
	res = tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
	assert(res == 0);
	
	return(c);
}

// Struct used in the thread for keyboard reading
struct InputKey
{
	void operator () ()
	{
		while (1)
		{
			char ch = getCharWithoutEnter();
			keys.push(ch);
		}
	}
};
