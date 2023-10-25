list=("tgcsa" "adj_list" "edge_list")

for i in $list
do
    valgrind --tool=massif --massif-out-file="${i}_massif.output" ./build/src/main --file=random_contacts.csv --queries=queries.txt --temporal_graph="${i}" &&
    ms_print "${i}_massif.output" > "${i}.output" &&
    rm "${i}_massif.output"
done