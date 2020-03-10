(def pattern (first *command-line-args*))
(if (nil? pattern)
    (do (println "Usage: find pattern") (. System exit -1)))

(defn compile_pattern [patt]
      (loop [source patt result []]
          (def result-char (take 1 source))
          (cond
           (empty? source) result
           :else (recur (drop 1 source) (conj result [(fn [cand] (= cand result-char)) 1])))))

(def matchfn (compile_pattern pattern))

(doseq [line (line-seq (java.io.BufferedReader. *in*))]
    (if (matchfn line)
        (println line)))
