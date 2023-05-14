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
Check ```output.json``` for more intuition.

## Setup and Environment
- Install WSL in Windows.
```
ps> wsl --install -d Ubuntu
```

- Set username and password. Please REMEMBER it.

- Run the following command and you will be required to type in the password set previously.
```
$ sudo apt update
$ sudo apt install build-essential
```

- Then run ``` gcc -v ``` and if you get something like this, it means your environment is properly settled.
```
gcc version 9.4.0 (Ubuntu 9.4.0-1ubuntu1~20.04.1)
```
- Compile and Run
```
$ make bonus
$ ./bonus sample.bvh
```

- You can try any other BVH file!
