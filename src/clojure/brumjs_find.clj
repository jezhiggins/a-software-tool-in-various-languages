(def pattern (first *command-line-args*))
(if (nil? pattern)
  (do (println "Usage: find pattern") (. System exit -1)))

(defn match-char? [cand, expected] (= cand expected))
(defn end-of-line? [cand] (nil? cand))

(defn compile-pattern [patt]
  (loop [source patt result []]
    (let [result-char (first source) rest-source (rest source)]
      (cond
       (empty? source) result
       (and (= \$ result-char) (empty? rest-source))
          (recur rest-source (conj result [end-of-line? 0]))
       :else (recur rest-source (conj result [(partial match-char? result-char) 1]))))))

(def compiled-pattern (compile-pattern pattern))

(defn match-line [line-seg]
  (loop [tests compiled-pattern line line-seg]
    (let [c (first line) ctest (first tests)]
      (let [test (first ctest) advance (first (rest ctest))]
        (if (test c)
          (let [remaining-tests (rest tests)]
            (if (empty? remaining-tests)
              true
              (recur (rest tests) (drop advance line))))
          false)))))

(defn matchfn [whole-line]
  (loop [line whole-line]
    (if (match-line line)
      true
      (let [rest-of-line (rest line)]
        (if (empty? rest-of-line)
          false
          (recur rest-of-line))))))

(doseq [line (line-seq (java.io.BufferedReader. *in*))]
    (if (matchfn line)
        (println line)))
