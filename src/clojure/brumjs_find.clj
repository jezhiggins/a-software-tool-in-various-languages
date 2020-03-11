(def pattern-string (first *command-line-args*))
(if (nil? pattern-string)
  (do (println "Usage: find pattern") (. System exit -1)))

(defn any-char [cand] true)
(defn match-char? [cand, expected] (= cand expected))
(defn end-of-line? [cand] (nil? cand))

(defn compile-pattern [patt]
  (loop [source patt result []]
    (let [result-char (first source) rest-source (rest source)]
      (let [test-fn
        (cond
         (empty? source) nil
         (= \? result-char) [any-char 1]
         (and (= \$ result-char) (empty? rest-source)) [end-of-line? 0]
         :else [(partial match-char? result-char) 1])]
        (if (nil? test-fn)
          result
          (recur rest-source (conj result test-fn)))))))

(def pattern (compile-pattern pattern-string))

(defn match-line [line-seg]
  (loop [tests pattern line line-seg]
    (let [c (first line) ctest (first tests)]
      (let [test (first ctest) advance (first (rest ctest))]
        (if (test c)
          (let [remaining-tests (rest tests)]
            (if (empty? remaining-tests)
              true
              (recur (rest tests) (drop advance line))))
          false)))))

(defn matcher [whole-line]
  (loop [line whole-line]
    (if (match-line line)
      true
      (let [rest-of-line (rest line)]
        (if (empty? rest-of-line)
          false
          (recur rest-of-line))))))

(doseq [line (line-seq (java.io.BufferedReader. *in*))]
    (if (matcher line)
        (println line)))
