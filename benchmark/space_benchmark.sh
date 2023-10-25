list=("tgcsa" "adj_list" "edge_list")

for i in $list
do
    valgrind --tool=massif --time-unit=ms --massif-out-file="massif_outputs/massif.out.${i}" ./build/src/main --file=random_contacts.csv --queries=queries.txt --temporal_graph="${i}" &&
    ms_print "massif_outputs/massif.out.${i}" > "massif_outputs/ms_print/ms_print_${i}" &&
done