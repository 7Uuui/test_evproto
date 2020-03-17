/*
 * Copyright (c) 2006-2007 Niels Provos <provos@citi.umich.edu>
 * Copyright (c) 2007-2009 Niels Provos and Nick Mathewson
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _EVENT2_RPC_H_
#define _EVENT2_RPC_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @file rpc.h
 *
 * This header files provides basic support for an RPC server and client.
 *
 * To support RPCs in a server, every supported RPC command needs to be
 * defined and registered.
 *
 * EVRPC_HEADER(SendCommand, Request, Reply);
 *
 *  SendCommand is the name of the RPC command.
 *  Request is the name of a structure generated by event_rpcgen.py.
 *    It contains all parameters relating to the SendCommand RPC.  The
 *    server needs to fill in the Reply structure.
 *  Reply is the name of a structure generated by event_rpcgen.py.  It
 *    contains the answer to the RPC.
 *
 * To register an RPC with an HTTP server, you need to first create an RPC
 * base with:
 *
 *   struct evrpc_base *base = evrpc_init(http);
 *
 * A specific RPC can then be registered with
 *
 * EVRPC_REGISTER(base, SendCommand, Request, Reply,  FunctionCB, arg);
 *
 * when the server receives an appropriately formatted RPC, the user callback
 * is invoked.   The callback needs to fill in the reply structure.
 *
 * void FunctionCB(EVRPC_STRUCT(SendCommand)* rpc, void *arg);
 *
 * To send the reply, call EVRPC_REQUEST_DONE(rpc);
 *
 * See the regression test for an example.
 */

/**
   Determines if the member has been set in the message

   @param msg the message to inspect
   @param member the member variable to test for presences
   @return 1 if it's present or 0 otherwise.
*/
#define EVTAG_HAS(msg, member) \
	((msg)->member##_set == 1)

#ifndef _EVENT2_RPC_COMPAT_H_

/**
   Assigns a value to the member in the message.

   @param msg the message to which to assign a value
   @param member the name of the member variable
   @param value the value to assign
*/
#define EVTAG_ASSIGN(msg, member, value) \
	(*(msg)->base->member##_assign)((msg), (value))
/**
   Assigns a value to the member in the message.

   @param msg the message to which to assign a value
   @param member the name of the member variable
   @param value the value to assign
   @param len the length of the value
*/
#define EVTAG_ASSIGN_WITH_LEN(msg, member, value, len)	\
	(*(msg)->base->member##_assign)((msg), (value), (len))
/**
   Returns the value for a member.

   @param msg the message from which to get the value
   @param member the name of the member variable
   @param pvalue a pointer to the variable to hold the value
   @return 0 on success, -1 otherwise.
*/
#define EVTAG_GET(msg, member, pvalue) \
	(*(msg)->base->member##_get)((msg), (pvalue))
/**
   Returns the value for a member.

   @param msg the message from which to get the value
   @param member the name of the member variable
   @param pvalue a pointer to the variable to hold the value
   @param plen a pointer to the length of the value
   @return 0 on success, -1 otherwise.
*/
#define EVTAG_GET_WITH_LEN(msg, member, pvalue, plen)	\
	(*(msg)->base->member##_get)((msg), (pvalue), (plen))

#endif  /* _EVENT2_RPC_COMPAT_H_ */

/**
   Adds a value to an array.
*/
#define EVTAG_ARRAY_ADD_VALUE(msg, member, value) \
	(*(msg)->base->member##_add)((msg), (value))
/**
   Allocates a new entry in the array and returns it.
*/
#define EVTAG_ARRAY_ADD(msg, member) \
	(*(msg)->base->member##_add)(msg)
/**
   Gets a variable at the specified offset from the array.
*/
#define EVTAG_ARRAY_GET(msg, member, offset, pvalue)	\
	(*(msg)->base->member##_get)((msg), (offset), (pvalue))
/**
   Returns the number of entries in the array.
*/
#define EVTAG_ARRAY_LEN(msg, member) ((msg)->member##_length)


struct evbuffer;
struct event_base;
struct evrpc_req_generic;
struct evrpc_request_wrapper;
struct evrpc;

/** The type of a specific RPC Message
 *
 * @param rpcname the name of the RPC message
 */
#define EVRPC_STRUCT(rpcname) struct evrpc_req__##rpcname

struct evhttp_request;
struct evrpc_status;
struct evrpc_hook_meta;

/** Creates the definitions and prototypes for an RPC
 *
 * You need to use EVRPC_HEADER to create structures and function prototypes
 * needed by the server and client implementation.  The structures have to be
 * defined in an .rpc file and converted to source code via event_rpcgen.py
 *
 * @param rpcname the name of the RPC
 * @param reqstruct the name of the RPC request structure
 * @param replystruct the name of the RPC reply structure
 * @see EVRPC_GENERATE()
 */
#define EVRPC_HEADER(rpcname, reqstruct, rplystruct) \
EVRPC_STRUCT(rpcname) {	\
	struct evrpc_hook_meta *hook_meta; \
	struct reqstruct* request; \
	struct rplystruct* reply; \
	struct evrpc* rpc; \
	struct evhttp_request* http_req; \
	struct evbuffer* rpc_data; \
};								     \
int evrpc_send_request_##rpcname(struct evrpc_pool *, \
    struct reqstruct *, struct rplystruct *, \
    void (*)(struct evrpc_status *, \
	struct reqstruct *, struct rplystruct *, void *cbarg),	\
    void *);

struct evrpc_pool;

/** use EVRPC_GENERATE instead */
struct evrpc_request_wrapper *evrpc_make_request_ctx(
	struct evrpc_pool *pool, void *request, void *reply,
	const char *rpcname,
	void (*req_marshal)(struct evbuffer*, void *),
	void (*rpl_clear)(void *),
	int (*rpl_unmarshal)(void *, struct evbuffer *),
	void (*cb)(struct evrpc_status *, void *, void *, void *),
	void *cbarg);

/** Creates a context structure that contains rpc specific information.
 *
 * EVRPC_MAKE_CTX is used to populate a RPC specific context that
 * contains information about marshaling the RPC data types.
 *
 * @param rpcname the name of the RPC
 * @param reqstruct the name of the RPC request structure
 * @param replystruct the name of the RPC reply structure
 * @param pool the evrpc_pool over which to make the request
 * @param request a pointer to the RPC request structure object
 * @param reply a pointer to the RPC reply structure object
 * @param cb the callback function to call when the RPC has completed
 * @param cbarg the argument to supply to the callback
 */
#define EVRPC_MAKE_CTX(rpcname, reqstruct, rplystruct, \
    pool, request, reply, cb, cbarg)					\
	evrpc_make_request_ctx(pool, request, reply,			\
	    #rpcname,							\
	    (void (*)(struct evbuffer *, void *))reqstruct##_marshal,	\
	    (void (*)(void *))rplystruct##_clear,			\
	    (int (*)(void *, struct evbuffer *))rplystruct##_unmarshal, \
	    (void (*)(struct evrpc_status *, void *, void *, void *))cb, \
	    cbarg)

/** Generates the code for receiving and sending an RPC message
 *
 * EVRPC_GENERATE is used to create the code corresponding to sending
 * and receiving a particular RPC message
 *
 * @param rpcname the name of the RPC
 * @param reqstruct the name of the RPC request structure
 * @param replystruct the name of the RPC reply structure
 * @see EVRPC_HEADER()
 */
#define EVRPC_GENERATE(rpcname, reqstruct, rplystruct)			\
	int evrpc_send_request_##rpcname(struct evrpc_pool *pool,	\
	    struct reqstruct *request, struct rplystruct *reply,	\
	    void (*cb)(struct evrpc_status *,				\
		struct reqstruct *, struct rplystruct *, void *cbarg),	\
	    void *cbarg) {						\
	return evrpc_send_request_generic(pool, request, reply,	\
	    (void (*)(struct evrpc_status *, void *, void *, void *))cb, \
	    cbarg,							\
	    #rpcname,							\
	    (void (*)(struct evbuffer *, void *))reqstruct##_marshal,	\
	    (void (*)(void *))rplystruct##_clear,			\
	    (int (*)(void *, struct evbuffer *))rplystruct##_unmarshal); \
}

/** Provides access to the HTTP request object underlying an RPC
 *
 * Access to the underlying http object; can be used to look at headers or
 * for getting the remote ip address
 *
 * @param rpc_req the rpc request structure provided to the server callback
 * @return an struct evhttp_request object that can be inspected for
 * HTTP headers or sender information.
 */
#define EVRPC_REQUEST_HTTP(rpc_req) (rpc_req)->http_req

/** completes the server response to an rpc request */
void evrpc_request_done(struct evrpc_req_generic *req);

/** accessors for request and reply */
void *evrpc_get_request(struct evrpc_req_generic *req);
void *evrpc_get_reply(struct evrpc_req_generic *req);

/** Creates the reply to an RPC request
 *
 * EVRPC_REQUEST_DONE is used to answer a request; the reply is expected
 * to have been filled in.  The request and reply pointers become invalid
 * after this call has finished.
 *
 * @param rpc_req the rpc request structure provided to the server callback
 */
#define EVRPC_REQUEST_DONE(rpc_req) do { \
  struct evrpc_req_generic *_req = (struct evrpc_req_generic *)(rpc_req); \
  evrpc_request_done(_req);					\
} while (0)


struct evrpc_base;
struct evhttp;

/* functions to start up the rpc system */

/** Creates a new rpc base from which RPC requests can be received
 *
 * @param server a pointer to an existing HTTP server
 * @return a newly allocated evrpc_base struct
 * @see evrpc_free()
 */
struct evrpc_base *evrpc_init(struct evhttp *server);

/**
 * Frees the evrpc base
 *
 * For now, you are responsible for making sure that no rpcs are ongoing.
 *
 * @param base the evrpc_base object to be freed
 * @see evrpc_init
 */
void evrpc_free(struct evrpc_base *base);

/** register RPCs with the HTTP Server
 *
 * registers a new RPC with the HTTP server, each RPC needs to have
 * a unique name under which it can be identified.
 *
 * @param base the evrpc_base structure in which the RPC should be
 *   registered.
 * @param name the name of the RPC
 * @param request the name of the RPC request structure
 * @param reply the name of the RPC reply structure
 * @param callback the callback that should be invoked when the RPC
 * is received.  The callback has the following prototype
 *   void (*callback)(EVRPC_STRUCT(Message)* rpc, void *arg)
 * @param cbarg an additional parameter that can be passed to the callback.
 *   The parameter can be used to carry around state.
 */
#define EVRPC_REGISTER(base, name, request, reply, callback, cbarg)	\
	evrpc_register_generic(base, #name,				\
	    (void (*)(struct evrpc_req_generic *, void *))callback, cbarg, \
	    (void *(*)(void *))request##_new, NULL,			\
	    (void (*)(void *))request##_free,				\
	    (int (*)(void *, struct evbuffer *))request##_unmarshal,	\
	    (void *(*)(void *))reply##_new, NULL,			\
	    (void (*)(void *))reply##_free, \
	    (int (*)(void *))reply##_complete, \
	    (void (*)(struct evbuffer *, void *))reply##_marshal)

/**
   Low level function for registering an RPC with a server.

   Use EVRPC_REGISTER() instead.

   @see EVRPC_REGISTER()
*/
int evrpc_register_rpc(struct evrpc_base *, struct evrpc *,
    void (*)(struct evrpc_req_generic*, void *), void *);

/**
 * Unregisters an already registered RPC
 *
 * @param base the evrpc_base object from which to unregister an RPC
 * @param name the name of the rpc to unregister
 * @return -1 on error or 0 when successful.
 * @see EVRPC_REGISTER()
 */
#define EVRPC_UNREGISTER(base, name) evrpc_unregister_rpc((base), #name)

int evrpc_unregister_rpc(struct evrpc_base *base, const char *name);

/*
 * Client-side RPC support
 */

struct evhttp_connection;
struct evrpc_status;

/** launches an RPC and sends it to the server
 *
 * EVRPC_MAKE_REQUEST() is used by the client to send an RPC to the server.
 *
 * @param name the name of the RPC
 * @param pool the evrpc_pool that contains the connection objects over which
 *   the request should be sent.
 * @param request a pointer to the RPC request structure - it contains the
 *   data to be sent to the server.
 * @param reply a pointer to the RPC reply structure.  It is going to be filled
 *   if the request was answered successfully
 * @param cb the callback to invoke when the RPC request has been answered
 * @param cbarg an additional argument to be passed to the client
 * @return 0 on success, -1 on failure
 */
#define EVRPC_MAKE_REQUEST(name, pool, request, reply, cb, cbarg)	\
	evrpc_send_request_##name((pool), (request), (reply), (cb), (cbarg))

/**
   Makes an RPC request based on the provided context.

   This is a low-level function and should not be used directly
   unless a custom context object is provided.  Use EVRPC_MAKE_REQUEST()
   instead.

   @param ctx a context from EVRPC_MAKE_CTX()
   @returns 0 on success, -1 otherwise.
   @see EVRPC_MAKE_REQUEST(), EVRPC_MAKE_CTX()
*/
int evrpc_make_request(struct evrpc_request_wrapper *ctx);

/** creates an rpc connection pool
 *
 * a pool has a number of connections associated with it.
 * rpc requests are always made via a pool.
 *
 * @param base a pointer to an struct event_based object; can be left NULL
 *   in singled-threaded applications
 * @return a newly allocated struct evrpc_pool object
 * @see evrpc_pool_free()
 */
struct evrpc_pool *evrpc_pool_new(struct event_base *base);
/** frees an rpc connection pool
 *
 * @param pool a pointer to an evrpc_pool allocated via evrpc_pool_new()
 * @see evrpc_pool_new()
 */
void evrpc_pool_free(struct evrpc_pool *pool);

/**
 * Adds a connection over which rpc can be dispatched to the pool.
 *
 * The connection object must have been newly created.
 *
 * @param pool the pool to which to add the connection
 * @param evcon the connection to add to the pool.
 */
void evrpc_pool_add_connection(struct evrpc_pool *pool,
    struct evhttp_connection *evcon);

/**
 * Removes a connection from the pool.
 *
 * The connection object must have been newly created.
 *
 * @param pool the pool from which to remove the connection
 * @param evcon the connection to remove from the pool.
 */
void evrpc_pool_remove_connection(struct evrpc_pool *pool,
    struct evhttp_connection *evcon);

/**
 * Sets the timeout in secs after which a request has to complete.  The
 * RPC is completely aborted if it does not complete by then.  Setting
 * the timeout to 0 means that it never timeouts and can be used to
 * implement callback type RPCs.
 *
 * Any connection already in the pool will be updated with the new
 * timeout.  Connections added to the pool after set_timeout has be
 * called receive the pool timeout only if no timeout has been set
 * for the connection itself.
 *
 * @param pool a pointer to a struct evrpc_pool object
 * @param timeout_in_secs the number of seconds after which a request should
 *   timeout and a failure be returned to the callback.
 */
void evrpc_pool_set_timeout(struct evrpc_pool *pool, int timeout_in_secs);

/**
 * Hooks for changing the input and output of RPCs; this can be used to
 * implement compression, authentication, encryption, ...
 */

enum EVRPC_HOOK_TYPE {
	EVRPC_INPUT,		/**< apply the function to an input hook */
	EVRPC_OUTPUT		/**< apply the function to an output hook */
};

#ifndef WIN32
/** Deprecated alias for EVRPC_INPUT.  Not available on windows, where it
 * conflicts with platform headers. */
#define INPUT EVRPC_INPUT
/** Deprecated alias for EVRPC_OUTPUT.  Not available on windows, where it
 * conflicts with platform headers. */
#define OUTPUT EVRPC_OUTPUT
#endif

/**
 * Return value from hook processing functions
 */

enum EVRPC_HOOK_RESULT {
	EVRPC_TERMINATE = -1,	/**< indicates the rpc should be terminated */
	EVRPC_CONTINUE = 0,	/**< continue processing the rpc */
	EVRPC_PAUSE = 1		/**< pause processing request until resumed */
};

/** adds a processing hook to either an rpc base or rpc pool
 *
 * If a hook returns TERMINATE, the processing is aborted. On CONTINUE,
 * the request is immediately processed after the hook returns.  If the
 * hook returns PAUSE, request processing stops until evrpc_resume_request()
 * has been called.
 *
 * The add functions return handles that can be used for removing hooks.
 *
 * @param vbase a pointer to either struct evrpc_base or struct evrpc_pool
 * @param hook_type either INPUT or OUTPUT
 * @param cb the callback to call when the hook is activated
 * @param cb_arg an additional argument for the callback
 * @return a handle to the hook so it can be removed later
 * @see evrpc_remove_hook()
 */
void *evrpc_add_hook(void *vbase,
    enum EVRPC_HOOK_TYPE hook_type,
    int (*cb)(void *, struct evhttp_request *, struct evbuffer *, void *),
    void *cb_arg);

/** removes a previously added hook
 *
 * @param vbase a pointer to either struct evrpc_base or struct evrpc_pool
 * @param hook_type either INPUT or OUTPUT
 * @param handle a handle returned by evrpc_add_hook()
 * @return 1 on success or 0 on failure
 * @see evrpc_add_hook()
 */
int evrpc_remove_hook(void *vbase,
    enum EVRPC_HOOK_TYPE hook_type,
    void *handle);

/** resume a paused request
 *
 * @param vbase a pointer to either struct evrpc_base or struct evrpc_pool
 * @param ctx the context pointer provided to the original hook call
 */
int
evrpc_resume_request(void *vbase, void *ctx, enum EVRPC_HOOK_RESULT res);

/** adds meta data to request
 *
 * evrpc_hook_add_meta() allows hooks to add meta data to a request. for
 * a client request, the meta data can be inserted by an outgoing request hook
 * and retrieved by the incoming request hook.
 *
 * @param ctx the context provided to the hook call
 * @param key a NUL-terminated c-string
 * @param data the data to be associated with the key
 * @param data_size the size of the data
 */
void evrpc_hook_add_meta(void *ctx, const char *key,
    const void *data, size_t data_size);

/** retrieves meta data previously associated
 *
 * evrpc_hook_find_meta() can be used to retrieve meta data associated to a
 * request by a previous hook.
 * @param ctx the context provided to the hook call
 * @param key a NUL-terminated c-string
 * @param data pointer to a data pointer that will contain the retrieved data
 * @param data_size pointer to the size of the data
 * @return 0 on success or -1 on failure
 */
int evrpc_hook_find_meta(void *ctx, const char *key,
    void **data, size_t *data_size);

/**
 * returns the connection object associated with the request
 *
 * @param ctx the context provided to the hook call
 * @return a pointer to the evhttp_connection object
 */
struct evhttp_connection *evrpc_hook_get_connection(void *ctx);

/**
   Function for sending a generic RPC request.

   Do not call this function directly, use EVRPC_MAKE_REQUEST() instead.

   @see EVRPC_MAKE_REQUEST()
 */
int evrpc_send_request_generic(struct evrpc_pool *pool,
    void *request, void *reply,
    void (*cb)(struct evrpc_status *, void *, void *, void *),
    void *cb_arg,
    const char *rpcname,
    void (*req_marshal)(struct evbuffer *, void *),
    void (*rpl_clear)(void *),
    int (*rpl_unmarshal)(void *, struct evbuffer *));

/**
   Function for registering a generic RPC with the RPC base.

   Do not call this function directly, use EVRPC_REGISTER() instead.

   @see EVRPC_REGISTER()
 */
int
evrpc_register_generic(struct evrpc_base *base, const char *name,
    void (*callback)(struct evrpc_req_generic *, void *), void *cbarg,
    void *(*req_new)(void *), void *req_new_arg, void (*req_free)(void *),
    int (*req_unmarshal)(void *, struct evbuffer *),
    void *(*rpl_new)(void *), void *rpl_new_arg, void (*rpl_free)(void *),
    int (*rpl_complete)(void *),
    void (*rpl_marshal)(struct evbuffer *, void *));

/** accessors for obscure and undocumented functionality */
struct evrpc_pool* evrpc_request_get_pool(struct evrpc_request_wrapper *ctx);
void evrpc_request_set_pool(struct evrpc_request_wrapper *ctx,
    struct evrpc_pool *pool);
void evrpc_request_set_cb(struct evrpc_request_wrapper *ctx,
    void (*cb)(struct evrpc_status*, void *request, void *reply, void *arg),
    void *cb_arg);

#ifdef __cplusplus
}
#endif

#endif /* _EVENT2_RPC_H_ */
