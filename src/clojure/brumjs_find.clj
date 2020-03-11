(def pattern (first *command-line-args*))
(if (nil? pattern)
  (do (println "Usage: find pattern") (. System exit -1)))

(defn compile_test [])

(defn compile_pattern [patt]
  (loop [source patt result []]
    (let [result-char (first source) rest-source (rest source)]
      (cond
       (empty? source) result
       (and (= \$ result-char) (empty? rest-source))
          (recur rest-source (conj result [(fn [cand] (nil? cand)) 0]))
       :else (recur rest-source (conj result [(fn [cand] (= cand result-char)) 1]))))))

(def compiled_pattern (compile_pattern pattern))

(defn match_line [line_seg]
  (loop [tests compiled_pattern line line_seg]
    (let [c (first line) ctest (first tests)]
      (let [test (first ctest) advance (first (rest ctest))]
        (if (test c)
          (let [remaining_tests (rest tests)]
            (if (empty? remaining_tests)
              true
              (recur (rest tests) (drop advance line))))
          false)))))

(defn matchfn [whole_line]
  (loop [line whole_line]
    (if (match_line line)
      true
      (let [rest_of_line (rest line)]
        (if (empty? rest_of_line)
          false
          (recur rest_of_line))))))

(doseq [line (line-seq (java.io.BufferedReader. *in*))]
    (if (matchfn line)
        (println line)))
