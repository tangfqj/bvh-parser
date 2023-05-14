# bvh-parser

## Description
BVH files are often used to describe the motion data of virtual figures, including the position and direction of each joint. This project is a simple BVH file parser, which takes in a BVH file and output a JSON file which recursively describes the skeleton information as follows:
```
- type: type of joint (ROOT, JOINT or End)
- name: name of joint
- offset: representing the offset relative to its parent joint
- channels
- motion
- children: contains its child joints' information (recursively)
```

## Setup and Environment

