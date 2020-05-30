
all: client

client:
	emcc main.c libdatachannel.a -s MAIN_MODULE=1 -s WASM=1 -s ASSERTIONS=1 -s NO_EXIT_RUNTIME=1 \
	-s "EXTRA_EXPORTED_RUNTIME_METHODS=['set_description', \
	'add_candidate', 'send_message', 'get_status', 'terminate']" \
	-o index.html

clean: 