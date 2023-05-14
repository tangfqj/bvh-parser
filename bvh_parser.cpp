#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <stack>
#include "bvh_parser.h"

// a naive bvh parser

using namespace std;

int main(int argc, char** argv) {
    joint root;
    META meta_data;
    ifstream file(argv[1]);

    string line, info;
    vector<vector<string>> lines;
    vector<string> line_data;
    // read in data and store it in "lines"
    if(file){
        while(getline(file, line)) {
            line_data.clear();
            istringstream record(line);
            while(record >> info){
                line_data.push_back(info);
            }
            lines.push_back(line_data);
        }
    } else{
        cerr << "Cannot open file!" << endl;
    }
    // process data
    queue<joint*> q;
    stack<joint*> stk;
    for(int i = 0; i < lines.size();) {
        string keyword = get_keyword(lines[i]);
        if (keyword == "HIERARCHY") {
            i++;
        } else if (keyword == "ROOT") {
            root.name = get_name(lines[i]);
            root.joint_type = "ROOT";
            split_offset(lines[i + 2], root.offset_x, root.offset_y, root.offset_z);
            root.channels = split_channels(lines[i + 3]);
            i += 4;
        } else if (keyword == "JOINT") {
            joint *child = new joint();
            child->name = get_name(lines[i]);
            child->joint_type = "JOINT";
            split_offset(lines[i + 2], child->offset_x, child->offset_y, child->offset_z);
            child->channels = split_channels(lines[i + 3]);
            if (stk.empty()) {
                root.children.push_back(child);
            } else {
                joint *father = stk.top();
                stk.pop();
                father->children.push_back(child);
                stk.push(father);
            }
            q.push(child);
            stk.push(child);
            i += 4;
        } else if (keyword == "End") {
            joint *child = new joint();
            child->joint_type = "End";
            split_offset(lines[i + 2], child->offset_x, child->offset_y, child->offset_z);
            if (stk.empty()) {
                child->name = root.name + "_End";
                root.children.push_back(child);
            } else {
                joint *father = stk.top();
                stk.pop();
                child->name = father->name + "_End";
                father->children.push_back(child);
                stk.push(father);
            }
            stk.push(child);
            i += 3;
        } else if (keyword == "}") {
            stk.pop();
            i++;
        } else if(keyword == "MOTION"){
            i++;
        } else if (keyword == "Frames:") {    // frame numbers
            meta_data.frame = get_frame(lines[i]);
            i++;
        } else if (keyword == "Frame") {      // frame_time
            meta_data.frame_time = get_frame_time(lines[i]);
            i++;
        } else {     // motion data
            for(int j = i; j < i + meta_data.frame; j++){
                vector<double> ch;
                // store motions of root
                for(int k = 0; k < root.channels.size(); k++){
                    ch.push_back(stod(lines[j][k]));
                }
                root.motion.push_back(ch);
                // store motions of children
                for(int m = root.channels.size(); m < lines[j].size();){
                    joint* child = q.front();
                    q.pop();
                    ch.clear();
                    int sz = child->channels.size();
                    for(int k = m; k < m + sz; k++){
                        ch.push_back(stod(lines[j][k]));
                    }
                    child->motion.push_back(ch);
                    q.push(child);
                    m += sz;
                }
            }
            break;
        }
    }

    jsonify(root, meta_data);
    file.close();
    return 0;
}

/* Implementation of helper functions */
string get_keyword(const vector<string>& data){
    return data[0];
}

string get_name(const vector<string>& data){
    return data[1];
}

void split_offset(const vector<string>& data, double& x, double& y, double& z){
    x = stod(data[1]);
    y = stod(data[2]);
    z = stod(data[3]);
}
vector<string> split_channels(const vector<string>& data){
    int n = stoi(data[1]);
    vector<string> ret;
    for(int i = 2; i < 2 + n; i++){
        ret.push_back(data[i]);
    }
    return ret;
}

int get_frame(const vector<string>& data){
    int frame = stoi(data[1]);
    return frame;
}

double get_frame_time(const vector<string>& data){
    double time = stod(data[2]);
    return time;
}


