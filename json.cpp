#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#include "bvh_parser.h"

using namespace std;
string indent(int n);
void output(ofstream& os, joint* root, int& idt);

void jsonify(joint root, META meta_data) {
    ofstream outfile;
    outfile.open("output.json");

    // output meta_data
    int idt = 0;
    outfile << "{" << endl;
    idt++;
    outfile << indent(idt) << "\"frame\": " << meta_data.frame << "," << endl;
    outfile << indent(idt) << "\"frame_time\": " << meta_data.frame_time << "," << endl;
    // output root
    outfile << indent(idt) << "\"joint\":" << endl;
    idt++;
    outfile << indent(idt) << "{" << endl;
    idt++;
    output(outfile, &root, idt);
    // end output
    idt--;
    outfile << indent(idt) << "}" << endl;
    outfile << "}";
    outfile.close();
}

string indent(int n){
    string idt = "";
    for(int i = 0; i < n; i++){
        idt += "\t";
    }
    return idt;
}


void output(ofstream& os, joint* child, int& idt){
    os << indent(idt) << "\"type\": \"" << child->joint_type << "\"," << endl;
    os << indent(idt) << "\"name\": \"" << child->name << "\"," << endl;
    os << indent(idt) << "\"offset\": " << "[" << child->offset_x << ", " << child->offset_y << ", " << child->offset_z << "]" << endl;
    os << indent(idt) << "\"channels\": " << "[";
    for(int i = 0; i < child->channels.size(); i++){
    	os << "\"" << child->channels[i] << "\"";
    	if(i != child->channels.size()-1)
    		os << ", ";
    }
    os << "]," << endl;
    os << indent(idt) << "\"motions\": " << "[" << endl;
    idt++;
    for(int i = 0; i < child->motion.size(); i++){
    	os << indent(idt) << "[";
    	for(int j = 0; j < child->channels.size(); j++){
    		os << child->motion[i][j];
    		if(j != child->channels.size()-1)
    			os << ", ";
    	}
    	os << "]";
    	if(i != child->motion.size()-1)
    		os << "," << endl;
    }
    idt--;
    os << endl;
    os << indent(idt) << "]," << endl;
    os << indent(idt) << "\"children\": " << "[" << endl;
    idt++;
    for(int i = 0; i < child->children.size(); i++){
    	os << indent(idt) << "{" << endl;
    	idt++;
    	output(os, child->children[i], idt);
    	idt--;
    	if(i != child->children.size()-1)
    		os << indent(idt) << "}," << endl;
    	else
    		os <<  indent(idt) << "}" << endl;
    }
    idt--;
    os << indent(idt) << "]" << endl;
    return;
}



