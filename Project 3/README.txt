Dane Backbier, dbackbie@u.rochester.edu, CSC 173, Project 3

Filter function works for built-in unary Boolean functions (not for ex. .LESSTHAN3
from the project description, because it's not built-in). Here are the .LESSTHAN3
and .lessthany functions if needed:

(defun .lessthan3 (X)
  (< X 3))

(defun .lessthany (X Y)
  (< X Y))

How to run:
1. cd into Project 3 folder
2. Execute java -jar "abcl-bin-1.9.2\abcl.jar" to open the Lisp REPL
3. Within REPL execute (load "Project3"), and it should output 'T'
4. Run any tests with (."functionName" (parameters))