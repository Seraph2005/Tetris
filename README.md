# Tetris
## Table Of Contents
- [Introduction](#introduction)
## Welcome👾
This is a terminal version of the famous game Tetris, you can choose the level and table measurements.


## Installing(in case you don't have an IDE)
- Clone the app in [github](https://github.com)
- Download [compiler](https://sourceforge.net/project/showfiles.php?group_id=2435&package_id=240780)
- Open the command line and change directory to the particular one where the source file is stored, using cd like so:
~~~
  cd C:\Documents
~~~
- Then, to compile, type in the command prompt:
~~~
gcc BluHatsTetris2.cpp -o outputfile.exe
~~~
- Finally, to run the code, type:
~~~
outputfile.exe
~~~

# About this app

## Usage
- 
## In the PROCESS...(Challenges & ideas)
- Security
  Passwords and E-mails are all hashed in the program.
- Unique identifiers
  - Users: username
  - SubSeraphits: Topic
  - Posts and comments: A unique UUID
- Timeline Problem
  The first problem I had was adding and removing posts from user's timeline(or any other list).
  Adding problem was because of a bad variable placement, But removing a post or comment in the middle of the for was a big problem. So, I made a new list in the begining and add removed contents to that list. After finishing the for, I removed all the contents in this list.
- Multiple reaction to the same content
  I used a HashMap which contains content's ID as key and the reaction as value. You can't add duplicate keys to HashMap.
- Removing posts or comments
  In case to remove a content, we have to remove it from several lists such as user's Upvoted contents and saved posts. We also have to reduce all user's karma who has anything to do with the post and the comment.
## Search engine
  I have a simple search engine which compares the entered string with all users usernames or subseraphits topic and show all the results containing the string.



