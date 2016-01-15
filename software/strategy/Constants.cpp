#include <Constants.h>

map<string, string> constants_map;

void initConstants()
{
	Config constants_cfg("constants.config");
    string constant_name;
    string constant_value;

	// Constant names are keys in constants config
	vector<string> constants = constants_cfg.keys();
    
    for(vector<string>::iterator it = constants.begin(); it != constants.end(); it++)
	{
		constant_name = *it;
        constant_value = constants_cfg.get(constant_name);
        
        //LOG(LEVEL_INFO) << "name: " << constant_name << " value: " << constant_value;
        insertNewConstant(constant_name, constant_value);
    }
}

void insertNewConstant(string constant_name, string value)
{
    constants_map.insert(pair<string, string>(constant_name, value));
}

double getValueFromConstant(string constant_name)
{
    if(constants_map[constant_name] == string(""))
    {
        LOG(LEVEL_ERROR) << "Constant " << constant_name << " is not declared";
    }
        
    return atof(constants_map[constant_name].c_str());
}
