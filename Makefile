CODE_DIR=src
.PHONY: run
run:
	$(MAKE) -C $(CODE_DIR) && cp src/run ./

clean:
	rm -f run && $(MAKE) clean -C $(CODE_DIR)
