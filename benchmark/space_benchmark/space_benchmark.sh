valgrind --tool=massif --time-unit=B --massif-out-file=tgcsa_massif.output ./build/src/main --file=random_contacts.csv ----queries=/queries.txt --temporal_graph=tgcsa
valgrind --tool=massif --time-unit=B --massif-out-file=adj_list_massif.output ./build/src/main --file=random_contacts.csv ----queries=/queries.txt --temporal_graph=adj_list
valgrind --tool=massif --time-unit=B --massif-out-file=edge_list_massif.output ./build/src/main --file=random_contacts.csv ----queries=/queries.txt --temporal_graph=edge_list