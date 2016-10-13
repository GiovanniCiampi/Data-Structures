PDFVIEWER = gv

test_exercice1:  test_exercice1.o rope.o rope_handling.o
	gcc test_exercice1.o rope.o rope_handling.o -o test_exercice1

test_exercice1.o: test_exercice1.c rope.h rope_handling.h
	gcc -Wall -c test_exercice1.c

#test_exercice2:  test_exercice2.o rope.o rope_handling.o
#	gcc test_exercice2.o rope.o rope_handling.o -o test_exercice2

test_exercice2:  test_exercice2.o rope.o rope_handling.o
	gcc test_exercice2.o rope.o to_string.o rope_handling.o -o test_exercice2

test_exercice2.o: test_exercice2.c rope.h rope_handling.h
	gcc -Wall -c test_exercice2.c



rope.o:rope.c rope.h
	gcc -Wall -c rope.c

rope_handling.o: rope_handling.c rope_handling.h rope.h
	gcc -Wall -c rope_handling.c



test_to_string.dot: test_exercice1
	./test_exercice1

test_destroy.dot test_destroy_init.dot test_sub_sub.dot test_sub_sub_init.dot test_sub_append.dot test_sub_append_init.dot test_push_sub_nodes.dot test_balanced_concat.dot: test_exercice2
	./test_exercice2

test_balanced_concat.pdf: test_balanced_concat.dot
	dot -Tpdf test_balanced_concat.dot -o test_balanced_concat.pdf

test_to_string.pdf: test_to_string.dot
	dot -Tpdf test_to_string.dot -o test_to_string.pdf

test_sub_sub_init.pdf: test_sub_sub_init.dot
	dot -Tpdf test_sub_sub_init.dot -o test_sub_sub_init.pdf

test_sub_sub.pdf: test_sub_sub.dot
	dot -Tpdf test_sub_sub.dot -o test_sub_sub.pdf

test_sub_append_init.pdf: test_sub_append_init.dot
	dot -Tpdf test_sub_append_init.dot -o test_sub_append_init.pdf

test_sub_append.pdf: test_sub_append.dot
	dot -Tpdf test_sub_append.dot -o test_sub_append.pdf

test_push_sub_nodes.pdf: test_push_sub_nodes.dot
	dot -Tpdf test_push_sub_nodes.dot -o test_push_sub_nodes.pdf

test_destroy_init.pdf: test_destroy_init.dot
	dot -Tpdf test_destroy_init.dot -o test_destroy_init.pdf

test_destroy.pdf: test_destroy.dot
	dot -Tpdf test_destroy.dot -o test_destroy.pdf

##### goals for viewing the results of the questions 1.5, 2.1, 2.2, 2.3, 2.4, 2.5

view_q14: test_to_string.pdf
	$(PDFVIEWER) test_to_string.pdf

view_q21: test_sub_sub.pdf test_sub_sub_init.pdf
	$(PDFVIEWER) test_sub_sub_init.pdf & $(PDFVIEWER) test_sub_sub.pdf

view_q22: test_sub_append.pdf test_sub_append_init.pdf
	$(PDFVIEWER) test_sub_append_init.pdf& $(PDFVIEWER) test_sub_append.pdf

view_q23: test_push_sub_nodes.pdf
	$(PDFVIEWER) test_push_sub_nodes.pdf

view_q24: test_destroy.pdf test_destroy_init.pdf
	$(PDFVIEWER) test_destroy_init.pdf& $(PDFVIEWER) test_destroy.pdf

view_q25: test_balanced_concat.pdf
	$(PDFVIEWER) test_balanced_concat.pdf

.PHONY: clean

clean:
	-rm *.dot
	-rm *.pdf
	-rm rope*.o test*.o
	-rm test_exercice1
	-rm test_exercice2
	-rm *~

