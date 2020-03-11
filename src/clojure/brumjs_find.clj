(defn any-char [cand at-start] true)
(defn match-char? [expected cand at-start] (= cand expected))
(defn start-of-line? [cand at-start] at-start)
(defn end-of-line? [cand at-start] (nil? cand))

(defn compile-pattern [patt]
  (loop [source patt result []]
    (let [result-char (first source) rest-source (rest source)]
      (let [test-fn
        (cond
         (empty? source) nil
         (= \? result-char) '(any-char 1)
         (and (= \% result-char) (= source patt)) '(start-of-line? 0)
         (and (= \$ result-char) (empty? rest-source)) '(end-of-line? 0)
         :else [(partial match-char? result-char) 1])]
        (if (nil? test-fn)
          result
          (recur rest-source (conj result test-fn)))))))

(defn match-line [pattern line-seg at-start]
  (loop [tests pattern line line-seg]
    (let [c (first line) ctest (first tests)]
      (let [test (first ctest) advance (first (rest ctest))]
        (if (test c at-start)
          (let [remaining-tests (rest tests)]
            (if (empty? remaining-tests)
              true
              (recur (rest tests) (drop advance line))))
          false)))))

(defn pattern-matches? [pattern whole-line]
  (loop [line whole-line at-start true]
    (if (match-line pattern line at-start)
      true
      (let [rest-of-line (rest line)]
        (if (empty? rest-of-line)
          false
          (recur rest-of-line false))))))

;; Here we go!
(def pattern-string (first *command-line-args*))
(if (nil? pattern-string)
  (do (println "Usage: find pattern") (. System exit -1)))

(def pattern (compile-pattern pattern-string))

(doseq [line (line-seq (java.io.BufferedReader. *in*))]
    (if (pattern-matches? pattern line)
        (println line)))
