#lang racket


; Modéliser le problème suivant en logique des propositions et résolvez-le à l’aide de la méthode de résolution :
; Un meurtre s’est produit au lieu dit “plateau de Cluedo”, vous êtes chargé de diriger l’enquête. Vous disposez de 3
; suspects, Dr Olive (O), Mlle Rose (R) et le Colonel Moutarde (M), avec 3 armes du crime potentielles, un chandelier (H), une
; clé anglaise (A), une corde (D) et 3 lieux possibles, la véranda (V), la cuisine (C) ou le bureau (B). Vous avez déjà réussi à
; récolter les indices suivants :
; 1. Il y a une et une seule arme du crime.
; 2. Il y a un et un seul lieu du crime.
; 3. Si le crime a eu lieu dans le bureau, la clé anglaise ne peut pas être l’arme du crime.
; 4. Si Mlle Rose est coupable, le crime a eu lieu dans la cuisine mais pas avec la corde.
; 5. Si le colonel Moutarde est l’assassin il n’a pas tué avec la clé anglaise.
; 6. Mlle Rose ou le colonel Moutarde est innocent (ou les deux).
; 7. Si Mlle Rose est innocente le crime a eu lieu dans le bureau ou avec la clé anglaise (ou les deux).
; 8. Le crime a eu lieu dans la véranda si et seulement si la clé anglaise est l’arme du crime.
; 9. Si le crime n’a pas eu lieu avec le chandelier ou si le docteur Olive est coupable (ou les deux) alors Mlle Rose est
; coupable aussi.
; 10. Le crime a eu lieu dans le bureau ou bien dans la cuisine.
; 11. Si le crime a eu lieu dans la cuisine alors l’arme du crime est la corde.
; 12. Enfin, vous êtes sûr qu’au moins un de vos trois suspects est coupable.
; Deux de vos coéquipiers sont certains d’avoir trouvé la solution mais ils proposent des conclusions contradictoires :
; 1. Noémie affirme que c’est le colonel Moutarde dans le bureau avec le chandelier,
; 2. alors que Arthur est persuadé que ce sont le Dr Olive et Mlle Rose dans la cuisine avec la corde.
;Est-ce que l’un des deux a raison ? Si oui, lequel ? ? ?





;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 1 Representation des propositions

(define F 'p)
(define G '(! toto))
(define H1 '(<-> (^ a c) (v (! b) (-> c (^ Bot Top)))))

(define (neg? F) (eq? F '!))
(define (and? F) (eq? F '^))
(define (or? F) (eq? F 'v))
(define (imp? F) (eq? F '->))
(define (equ? F) (eq? F '<->))
(define (top? F) (eq? F 'Top))
(define (bot? F) (eq? F 'Bot))
(define (symbLog? F) (or (top? F) (bot? F) (and? F) (or? F) (neg? F) (imp? F) (equ? F)))
(define (conBin? F) (or (and? F) (or? F) (imp? F) (equ? F)))
(define (symbProp? F) (and (symbol? F) (not (symbLog? F))))
(define (atomicFbf? F) (or (symbProp? F) (top? F) (bot? F)))
(define (fbf? F)
  (cond ((atomicFbf? F) 					   #t )
        ((list? F) (cond ((and (= (length F) 2) (neg? (car F)))    (fbf? (cadr F)))
                         ((and (= (length F) 3) (conBin? (car F))) (and (fbf? (cadr F)) (fbf? (caddr F))) )
                         (else #f)))
        (else #f)))
(define (conRac F) (car F))
(define (fils F) (cadr F))
(define (filsG F) (cadr F))
(define (filsD F) (caddr F))
(define (negFbf? F) (and (not (atomicFbf? F)) (neg? (conRac F))))
(define (conjFbf? F) (and (not (atomicFbf? F)) (and? (conRac F))))
(define (disjFbf? F) (and (not (atomicFbf? F)) (or? (conRac F))))
(define (implFbf? F) (and (not (atomicFbf? F)) (imp? (conRac F))))
(define (equiFbf? F) (and (not (atomicFbf? F)) (equ? (conRac F))))

; Q1
(display "\nQ1\n")
(display "F => ") F
(display "G => ") G
(display "H1 => ") H1
(define F1 '(<-> (^ a b) (v (! a) b)))
(define F2 '(v (! (^ a (! b))) (! (-> a b))))
(define F3 '(^ (! (-> a (v a b))) (! (! (^ a (v b (! c)))))))
(define F4 '(^ (v (v (! a) b) d) (^ (v (! d) c) (^ (v c a) (^ (v (! c) b) (^ (v (! c) (! b)) (v (! b) d)))))))          


; Q2
(display "\nQ2\n")
(display "(fbf? F) => ") (fbf? F)
(display "(fbf? G) => ") (fbf? G)
(display "(fbf? H1) => ") (fbf? H1)
(display "(fbf? '(! a b)) => ") (fbf? '(! a b))
(fbf? F1)
(fbf? F2)
(fbf? F3)
(fbf? F4)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 2 Syntaxe des propositions

;Q3
(define (nbc F)
  (cond ((atomicFbf? F) 0)
        ((negFbf? F) (+ 1 (nbc (fils F))))
        (else (+ 1 (nbc (filsG F)) (nbc (filsD F))))))

;Q4
(define (prof f)
  (cond ((atomicFbf? f) 0)
        ((negFbf? f) (+ 1 (prof (fils f))))
        (else (max (+ 1 (prof (filsG f))) (+ 1 (prof (filsD f)))))))

;Q5
(define (ensSP F) ;(ensSP F1) => '(a b)
  (cond ((atomicFbf? F) (set-add '() F))
        ((null? F) '())
        ((negFbf? F) (set-union (ensSP (cadr F))))
        (else (set-union (ensSP (cadr F)) (ensSP (caddr F))))))

;Q6
(define (affiche f)
  (cond
    ((atomicFbf? f) (display f))
    ((negFbf? f) (begin (display "(") (display "¬") (affiche (fils f)) (display ")")))
    (else (begin (display "(") (affiche (filsG f)) (display " ") (display (car f)) (display " ") (affiche (filsD f)) (display ")")))
    ))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 3 Semantique

(define I '((a . 0) (b . 1)))

;Q7
(define I1 '((a . 1) (c . 1) (b . 0)))
(define I2 '((a . 0) (b . 0) (c . 0)))
(define I3 '((a . 1) (b . 1) (c . 1)))

;Q8
(define (intSymb s I)
  (cond ((eq? s (car (set-first I))) (cdr (set-first I)))
        (else (intSymb s (cdr I)))))
(display "\nQ8\n")
(intSymb 'a I1)

;Q9
(define (intAnd v1 v2) (* v1 v2))
(define intTop 1)
(define intBot 0)
(define (intNeg v) (+ (* -1 v) 1))
(define (intOr v1 v2) (max v1 v2))
(define (intImp v1 v2) (if (eq? v1 0) 1 v2))
(define (intEqu v1 v2) (if (eq? v1 v2) 1 0))

;Q10
(define (valV f i)
  (cond ((symbProp? f) (intSymb f i))
        ((top? f) intTop)
        ((bot? f) intBot)
        ((negFbf? f) (intNeg (valV (fils f) i)))
        ((and? (car f)) (intAnd (valV (filsG f) i) (valV (filsD f) i)))
        ((or? (car f)) (intOr (valV (filsG f) i) (valV (filsD f) i)))
        ((imp? (car f)) (intImp (valV (filsG f) i) (valV (filsD f) i)))
        ((equ? (car f)) (intEqu (valV (filsG f) i) (valV (filsD f) i)))
        (else 0)))
(display "\nQ10\n")
(valV F1 I1)

;Q11
(define (modele? i F)
  (eq? (valV F i) 1))
  
;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 4 Satisfiabilite, Validite

;Q12
(define EI
  (list
   (list (cons 'p 0) (cons 'q 0))
   (list (cons 'p 0) (cons 'q 1))
   (list (cons 'p 1) (cons 'q 0))
   (list (cons 'p 1) (cons 'q 1))))

;Q13
(define (ensInt ensSymb)
  (if (set-empty? ensSymb) '(())
      (let ( (EI (ensInt (cdr ensSymb))))
                 (append (map (lambda (I)
                                (set-add I (cons (car ensSymb) 0))) EI)
                         (map (lambda (I)
                                (set-add I (cons (car ensSymb) 1))) EI)))))
(display "\nQ13\n")
(ensInt '(a b c))
(ensInt '(p q))


;Q14
(define (satisfiable? fbf)
  (ormap (lambda (i) (modele? i fbf)) (ensInt (ensSP fbf))))
(display "\nQ14\n")
(satisfiable? 'a)
(satisfiable? '(! a))
(satisfiable? '(^ a b))
(satisfiable? '(^ (^ a b) (! a)))

;Q15
(define (valide? fbf)
  (andmap (lambda (i) (modele? i fbf)) (ensInt (ensSP fbf))))
(display "\nQ15\n")
(valide? 'a)
(valide? '(! a))
(valide? '(v a b))
(valide? '(v (v a b) (! a)))

;Q16
(define (insatisfiable? fbf)
  (eq? '()
       (filter-map (lambda (i) (eq? #t (modele? i fbf))) (ensInt (ensSP fbf)))))

(define (insatisfiable2? fbf)
  (not (ormap (lambda (i) (modele? i fbf)) (ensInt (ensSP fbf)))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 5 Equivalence, Consequence

;Q17
(define (equivalent? fbf1 fbf2)
  (andmap (lambda (i)
            (eq? (valV fbf1 i) (valV fbf2 i)))
          (ensInt (set-union (ensSP fbf1) (ensSP fbf2)))))
(display "\nQ17\n")
(equivalent? '(v (v a b) (! a)) '(! (^ (^ c d) (! c))))
(equivalent? '(v a (! a)) '(! (^ c (^ b (! b)))))

;Q17 bis
(define (equivalent2? fbf1 fbf2)
  (valide? (list '<-> fbf1 fbf2)))
(equivalent2? '(v (v a b) (! a)) '(! (^ (^ c d) (! c))))
(equivalent2? '(v a (! a)) '(! (^ c (^ b (! b)))))

;Q18
(define (consequence2? F1 F2)
  (andmap (lambda (i)
            (if (and (eq? (valV F1 i) 1) (= (valV F2 i) 0)) #f #t))
          (ensInt (set-union (ensSP F1) (ensSP F2)))))
(display "\nQ18\n")
(consequence2? 'a '(v a b))
(not (consequence2? 'a '(^ a b)))
(consequence2? '(v (v a b) (! a)) '(! (^ (^ c d) (! c))))
(consequence2? '(^ (^ a b) (! a)) '(v c d))
(consequence2? '(^ p (-> p q)) 'q) ; {p, p->q} |= q (modus ponens)
(consequence2? '(^ (! q) (-> p q)) '(! p)) ;{ ¬q,p->q} |= ¬p (modus tollens)

(define (consequence2v2? f g)
  (insatisfiable? (list '^ f (list '! g)))
  )

(define (consequence2v3? f g)
  (valide? (list '-> f g))
  )

;Q19
(define (ensSPallFbf F)
  (cond ((set-empty? F) '())
        ((not (fbf? (car F))) (ensSPallFbf (cdr F)))
        ((fbf? (car F)) (list (ensSP (car F))
                 (ensSPallFbf (cdr F))))))
                  
(display "\nQ19\n")
(ensSPallFbf F1)

;Q20
(define (modeleCommun? i ensFBF)
  (cond ((set-empty? ensFBF))
        ((modele? i (car ensFBF)) (modeleCommun? i (cdr ensFBF)))
        (else #f)))
(define (modeleCommen2? i ensFBF)
  (andmap (lambda (fbf) (modele? i fbf)) ensFBF))

;Q21
(define (contradictoire? ensFBF)
  (not (ormap (lambda (i) (modeleCommun? i ensFBF)) (ensInt (ensSPallFbf ensFBF)))))

(define (contradictoire2? ensFBF)
  (andmap (lambda (i) (not (modeleCommun? i ensFBF))) (ensInt (ensSPallFbf ensFBF))))
        
;Q22

;Q23
(define (conjonction EF) ; EF est une ensemble de fbf
  (cond  ((set-empty? EF) 'Top)
         ((set-empty? (set-rest EF)) (set-first EF))
         (else (list '^ (set-first EF) (conjonction (set-rest EF))))))

;(define (consequenceV? EH C)
   
;Q24


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 6 Mise sous forme conjonctive

;Q25
(define (oteEqu F)
  (cond ((atomicFbf? F) F)
        ((negFbf? F) (set-add (list (oteEqu (fils F))) '!))
        ((not (equiFbf?  F)) (set-add (list (oteEqu (filsG F)) (oteEqu (filsD F))) (car F))) 
        (else (set-add (list  ;c'est <->
              (set-add (list (oteEqu (filsG F)) (oteEqu (filsD F))) '->)
              (set-add (list (oteEqu (filsD F)) (oteEqu (filsG F))) '->))
               '^))))  

(display "\nQ25\n")
(oteEqu '(<-> a b))
(oteEqu '(! (<-> a b)))

;Q26
(define (oteImp F)
  (cond ((atomicFbf? F) F)
        ((negFbf? F) (set-add (list (oteImp (fils F))) '!))
        ((not (implFbf? F)) (set-add (list (oteImp (filsG F)) (oteImp (filsD F))) (car F)))
        (else (set-add (list  ;c'est ->
              (set-add (list (oteImp (filsG F))) '!)
              (oteImp (filsD F))) 
              'v))))

(display "\nQ26\n")
(oteImp '(-> a b))
(oteImp (oteEqu '(<-> a b)))
                        
;Q27
(define (oteCste F)
  (cond ((atomicFbf? F) F)
        ((valide? F) 'Top)
        ((insatisfiable? F) 'Bot)
        ((negFbf? F) (set-add (list (oteCste (fils F))) '!))
        (else (set-add (list
              (oteCste (filsG F)) (oteCste (filsD F)))
               (car F)))))
(display "\nQ27\n")
(oteCste '(v (^ a (! a)) c))

;Q28
(define (redNeg F)
  (cond ((symbProp? F) F) ; cas d'un symbole propositionnel
        ((not (negFbf? F)) (set-add (list (redNeg (filsG F)) (redNeg (filsD F))) (car F)))  ; cas d'un connecteur racine ^ ou v
        (else  ; cas de la négation en connecteur racine ==> on regarde son fils
         (cond ((symbProp? (fils F)) F) ; littéral négatif
               ((negFbf? (fils F)) (redNeg (cadadr F)))    ; deux négations ==> équivalence de la double négation 
               ((conjFbf? (fils F)) (set-add (list
                                              (redNeg (set-add (list (filsG (fils F))) '!))
                                              (redNeg (set-add (list (filsD (fils F))) '!))) 'v)) ; négation d'une conjonction ==> équivalence de De Morgan
               (else (set-add (list           ; négation d'une disjonction ==> équivalence de De Morgan
                                     (redNeg (set-add (list (filsG (fils F))) '!)) 
                                     (redNeg (set-add (list (filsD (fils F))) '!))) '^))
               )))) 

(display "\nQ28\n")
(redNeg '(! (^ (v a b) (^ b c))))
(affiche (redNeg '(! (^ (v a b) (^ b c)))))

;Q29
(define (distOu F)
  (cond ((symbProp? F) F) 
        ((negFbf? F) (set-add (list (distOu (fils F))) '!))   
        ((conjFbf? F) (set-add (list (distOu (filsG F)) (distOu (filsD F)))  '^))     
        (else          ; c'est donc une disjonction
         (let ( (Fg (distOu (filsG F))) (Fd (distOu (filsD F))) )  
           (cond ((conjFbf? Fg)	(list '^   (distOu (list 'v (filsG Fg) Fd))   (distOu (list 'v (filsD Fg) Fd))))
                 ((conjFbf? Fd)	(list '^   (distOu (list 'v Fg (filsG Fd)))   (distOu (list 'v Fg (filsD Fd)))))
                 (else 			; il n'y a plus de ^ dans les sous-formules
                  (list 'v   Fg   Fd)))))))

(display "\n\nQ29\n")
(distOu '(v (^ a b) c))

;Q30
(define (formeConj fbf)
  (distOu (redNeg (oteImp (oteEqu fbf)))))

(display "\n\nQ30\n")
(define conj '(v (-> p q) (! (<-> q p))))
(affiche conj) (display "\n")
(affiche (formeConj conj))

  
;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 7 Mise sous forme clausale

; Exemple de clause et forme clausale
(define exClause '( p (! r) t))
(define exFormeClausale '( (p (! p))  (p q (! r))  ((! r) s)  (p (! r) t)  (p ( ! r))  (r (! t))  (s t) (p (! s))   ((! p ) (! s))))

; Fonction permettant de tester si une fbf est un littéral et d'obtenir le littéral opposé d'un littéral
(define (litteral? F) (or (symbProp? F) (and (negFbf? F) (symbProp? (fils F)))))
(define (oppose L) (if (symbProp? L) (list '! L) (fils L)))
  
; Fonctions permettant de manipuler des ensembles d'ensembles
(define (setSet-member? EC C)
  (cond ((set-empty? EC) #f)
        ((set=? (set-first EC) C) #t)
        (else (setSet-member? (set-rest EC) C))))

(define (setSet-add EC C)
  (cond ((set-empty? EC) (list C))
        ((set=? (set-first EC) C) EC)
        (else (set-add (setSet-add (set-rest EC) C) (set-first EC)))))

(define (setSet-union EC1 EC2)
  (if (set-empty? EC2) EC1
      (setSet-union (setSet-add EC1 (set-first EC2)) (set-rest EC2))))

;Q31
(define (transClause fbf)
  (if (litteral? fbf) (list fbf)
      (set-union (transClause (filsG fbf)) (transClause (filsD fbf)))))

(display "\n\nQ31\n")
(display "(transClause '(! a))=> ") (transClause '(! a))
(display "(transClause '(v a b))=> ") (transClause '(v a b))
(display "(transClause '(v (! a) b))=> ") (transClause '(v (! a)b))        
  
;Q32
(define (transEnsClause fbf)
  (if (conjFbf? fbf) (setSet-union (transEnsClause (filsG fbf)) (transEnsClause (filsD fbf)))
      (list (transClause fbf))))
(display "\n\nQ32\n")
(transEnsClause (formeConj F1))


;Q33
(define (formeClausale f)
(transEnsClause (formeConj f)))
;celui en bas est meilleure car il subsume déjà
(define (formeClausale2 fbf)
  (let ([C (formeConj fbf)])
    (cond ((valide? C) '())
          ((conjFbf? C) (setSet-union (formeClausale2 (filsG C)) (formeClausale2 (filsD C))))
          (else (list (transClause C))))))

(display "\n\nQ33\n")
(formeClausale F1)
(formeClausale2 F1)

;Q34
(define (tautologique C)
  (cond ((valide? C) #t)
        ((conjFbf? C) (or (tautologique (filsG C)) (tautologique (filsD C))))
        (else #f)))
(display "\n\nQ34\n")
(tautologique (formeConj F1))

;Q35


;Q36
(define (formeClausaleV2 fbf)
  (let ([C (formeConj fbf)])
    (cond ((valide? C) '())
          ((conjFbf? C) (setSet-union (formeClausaleV2 (filsG C)) (formeClausaleV2 (filsD C))))
          (else (list (transClause C))))))

;;;;;;;;;;;;;;;
; 8  Resolution

;Q37
;(define (resolvable c1 c2)
 ; (cond ((if (and (litteral? c1) (litteral? c2))
  
;Q38
        
;Q39
;(define (ClauseVideParResolution FC)
 ; (if (null? (cadr FC)) ;si la forme clausale ne contient qu'une seule clause alors c'est faux
     ; #f
     ; (if (null? FC) ;si il est vide
        ;  #t
       ;   ;sinon il a au moins 2 clauses
      ;    ((let ((p '()) (r '()))
     ;        (letrec ((res1 (FC))) ;premier boucle
    ;           (if (null? (FC)) ; cas d'arret de la premier boucle
   ;                '()
  ;                 ((letrec ((res2 (set-rest FC)) ;cas d'arret de la deuxieme boucle
 ;                            '()
;
  ;                           (if (resolvable (set-first FC) (set-first (set-rest FC))) ; si resolvable
 ;                                (begin (set! r (resolvante (set-first FC) (set-first (set-rest (set-rest FC))))
                                              
             

;Q40


;;;;;;;;;;;;;;;
; 9 Application

;Q41                    ;1 a raison, 2 a tort
;les suspects
(define O '(Dr Olive est coupable))
(define R '(Mlle Rose est coupable))
(define M '(Colonel Moutarde est coupable))

;les armes
(define H '(chandelier est utilisé))
(define A '(clé anglaise est utilisé))
(define D '(une corde est utilisé))

;les lieux
(define V '(véranda))
(define C '(cuisine))
(define B '(bureau))

;les indices
(define P1 '(v (^ H (^ (! A) (! D)))
               (v (^ (! H) (^ A (! D))) (^ (! H) (^ (! A) D)))))
(define P2 '(v (^ V (^ (! C) (! B)))
               (v (^ (! V) (^ C (! B))) (^ (! V) (^ (! C) B)))))
(define P3 '(-> B (! A)))
(define P4 '(-> R (^ C (! D))))
(define P5 '(-> M (! A)))
(define P6 '(v (! R) (! M)))
(define P7 '(-> (! R) (v B A)))
(define P8 '(<-> V A))
(define P9 '(-> (v (! H) O) R))
(define P10 '(v B C))
(define P11 '(-> C D))
(define P12 '(v O (v R M)))


(define X (list '^ P1(list '^ P2 (list '^ P3 (list '^ P4 (list '^ P5 (list '^ P6 (list '^ P7 (list '^ P8 (list '^ P9 (list '^ P10 (list '^ P11 P12))))))))))))

;les solutions des coéquipiers
(define Noémie '(^ M (^ B H)))
(define Arthur '(^ (^ O R) (^ C D)))
(define (raison? A)
  (valide? (list '-> X A)))

(display "\n\nQ41\n")
(if (raison? Noémie) (display "Noémie a raison\n") (display "Noémie n'a pas de raison\n"))
(if (raison? Arthur) (display "Arthur a raison\n") (display "Arthur n'a pas de raison\n"))
                      

;;;;;;;;;;;;;;;
; 10 Evaluation

