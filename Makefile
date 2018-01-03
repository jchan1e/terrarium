CODE_DIR=src
.PHONY: run
run:
	$(MAKE) -C $(CODE_DIR) run && cp $(CODE_DIR)/run ./

test:
	$(MAKE) -C $(CODE_DIR) test

clean:
	rm -f run && $(MAKE) clean -C $(CODE_DIR)
