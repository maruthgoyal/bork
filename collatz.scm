(define (f n)
	(if (= n 1)
		1
		(if (= (mod n 2) 1)
			(+ 1 (f (+ (* n 3) 1)))
			(+ 1 (f (/ n 2)))
		)
	)
)

(display (f 5))