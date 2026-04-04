; Dane Backbier, dbackbie@u.rochester.edu, CSC 173, Project 3

; List Functions

; Returns the number of elements in the list L.
(defun .length (L)
  (if (null L) 0
    (+ 1 (.length (cdr L)))))

; Returns the element from list L at index I (a number), or nil if there is no such element.
(defun .element-at (L I)
  (if (or (< I 0) (null L)) nil
    (if (= I 0) (car L)
      (.element-at (cdr L) (- I 1)))))

; Returns a list containing only those elements of L for which the unary Boolean function F returns true (non-nil).
(defun .filter (F L)
  (if (null L) nil
    (if (funcall F (car L))
      (cons (car L) (.filter F (cdr L)))
      (.filter F (cdr L)))))

; Assuming that list L contains numbers, returns their sum.
(defun .sum (L)
  (if (null L) 0
    (+ (car L) (.sum (cdr L)))))

; Set Functions

; Returns true (non-nil) if X is an element of the set S (test with equalp), otherwise false (nil)
(defun .element-of (X S)
  (if (null S) nil
    (if (equalp X (car S)) T
      (.element-of X (cdr S)))))

; Returns the set that is the difference of sets S1 and S2 (that
; is: S1 \S2, also written simply S1 −S2: the set containing all the elements of S1 that
; are not also elements of S2); test with equalp.
(defun .difference (S1 S2)
  (if (null S1) nil
    (if (.element-of (car S1) S2) (.difference (cdr S1) S2)
      (cons (car S1) (.difference (cdr S1) S2)))))

; Returns true (non-nil) if S1 is a subset of or equal to set S2
; (that is, if S1 ⊆ S2), otherwise returns false (nil); test with equalp.
(defun .subseteq (S1 S2)
  (if (null S1) T
    (if (.element-of (car S1) S2) (.subseteq (cdr S1) S2)
      nil)))

; Extra (non-set) function
; Returns the result of applying function F N times to argument X.
(defun .ntimes (F X N)
  (if (= N 0) X
    (.ntimes F (funcall F X) (- N 1))))

; Math Functions

; Returns true (non-nil) if the complex numbers C1 and C2 are
; equal. Two complex numbers a+bi and c+di are equal iff their real parts are equal
; and their imaginary parts are equal (that is, a = c and b = d). You may assume
; that complex numbers are represented using lists containing two elements where
; the first element is the real part and the second element is the imaginary part. Test
; numbers using =.
(defun .complex= (C1 C2)
  (and (= (car C1) (car C2)) (= (car (cdr C1)) (car (cdr C2)))))

; Returns the dot product of vectors V1 and V2.
(defun .dot-product (V1 V2)
  (if (or (null V1) (null V2)) 0
    (+ (* (car V1) (car V2)) (.dot-product (cdr V1) (cdr V2)))))

; Returns the value of X to the power Y (x^y; you may assume that Y is an integer).
(defun .pow (X Y)
  (if (= Y 0) 1
    (if (> Y 0) (* X (.pow X (- Y 1)))
      (/ (.pow X (+ Y 1)) X))))

; Monthly mortgage payment p for principal amount P, monthly interest rate R, for N months
(defun .monthly-payment (P R N)
  (/ (* R P) (- 1 (/ 1 (.pow (+ R 1) N)))))