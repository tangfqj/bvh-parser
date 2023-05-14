#ifndef BVH_PARSER_H
#define BVH_PARSER_H
#include <string>
#include <vector>
#include <queue>

using std::string;
using std::vector;
using std::queue;

struct joint {
    string name;
    double offset_x, offset_y, offset_z;
    vector<joint*> children;
    vector<string> channels;
    vector<vector<double>> motion;
    string joint_type;
};

struct META {
    int frame;
    double frame_time;
};

void jsonify (joint, META);
string get_keyword(const vector<string>& line);
string get_name(const vector<string>& data);
void split_offset(const vector<string>& data, double& x, double& y, double& z);
vector<string> split_channels(const vector<string>& data);
int get_frame(const vector<string>& data);
double get_frame_time(const vector<string>& data);
//void process_motion(const vector<string>& data, queue<joint*>& q, joint& root);
#endif