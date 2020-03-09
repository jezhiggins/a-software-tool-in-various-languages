(defn brumjs_find [line] (println line))

(doseq [line (line-seq (java.io.BufferedReader. *in*))]
  (brumjs_find line))
