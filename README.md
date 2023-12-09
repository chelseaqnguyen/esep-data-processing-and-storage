# esep-data-processing-and-storage
This is a database transaction simulator. There are several commands that the user can input (put, get, begin, commit, rollback, exit) to see how database transactions occur.
To start a transaction, the user can type "begin". The user can type the individual works "put", "get", "commit", and so on to make transactions. the program will output appropriate responses on how you order the commands.

Instructions on running the file:

- start a new project on CLion
- place the file "InMemoryDB.cpp" in the project folder; place it one directory outside of cmake-build-debug
- make sure the file is added to the the executable in CMakeLists.txt
- run the program and test it out!

Possible modifications to this assignment:
    I think the links provided provide a basic introduction to how database transactions work; however, it might be clearer to include a visualization of how they work as well. I personally looked up additional resources to try and understand the order in the way they occur. Also, it would be helpful to clarify the format in how the graders wanted to test out our programs. Because there was not much explanation, I just assumed the design of the program was up to our own separate interpretations.
