/*
 * Generated by Apache::Constants::Exports::gen_ctags, do not edit!!!
 */  
static char *ETAG_http[] = { 
   "HTTP_METHOD_NOT_ALLOWED",
   "HTTP_NOT_ACCEPTABLE",
   "HTTP_LENGTH_REQUIRED",
   "HTTP_PRECONDITION_FAILED",
   "HTTP_SERVICE_UNAVAILABLE",
   "HTTP_VARIANT_ALSO_VARIES",
   "HTTP_NO_CONTENT",
   "HTTP_METHOD_NOT_ALLOWED",
   "HTTP_NOT_ACCEPTABLE",
   "HTTP_LENGTH_REQUIRED",
   "HTTP_PRECONDITION_FAILED",
   "HTTP_SERVICE_UNAVAILABLE",
   "HTTP_VARIANT_ALSO_VARIES",
   NULL,
};
static char *ETAG_satisfy[] = { 
   "SATISFY_ALL",
   "SATISFY_ANY",
   "SATISFY_NOSPEC",
   NULL,
};
static char *ETAG_methods[] = { 
   "M_CONNECT",
   "M_DELETE",
   "M_GET",
   "M_INVALID",
   "M_OPTIONS",
   "M_POST",
   "M_PUT",
   "M_TRACE",
   "METHODS",
   NULL,
};
static char *ETAG_types[] = { 
   "DIR_MAGIC_TYPE",
   NULL,
};
static char *ETAG_config[] = { 
   "DECLINE_CMD",
   NULL,
};
static char *ETAG_server[] = { 
   "MODULE_MAGIC_NUMBER",
   "SERVER_VERSION",
   "SERVER_SUBVERSION",
   "SERVER_BUILT",
   NULL,
};
static char *ETAG_common[] = { 
   "OK",
   "DECLINED",
   "DONE",
   "NOT_FOUND",
   "FORBIDDEN",
   "AUTH_REQUIRED",
   "SERVER_ERROR",
   NULL,
};
static char *ETAG_remotehost[] = { 
   "REMOTE_HOST",
   "REMOTE_NAME",
   "REMOTE_NOLOOKUP",
   "REMOTE_DOUBLE_REV",
   NULL,
};
static char *ETAG_response_codes[] = { 
   "OK",
   "DECLINED",
   "DONE",
   "NOT_FOUND",
   "FORBIDDEN",
   "AUTH_REQUIRED",
   "SERVER_ERROR",
   "DOCUMENT_FOLLOWS",
   "MOVED",
   "REDIRECT",
   "USE_LOCAL_COPY",
   "BAD_REQUEST",
   "BAD_GATEWAY",
   "RESPONSE_CODES",
   "NOT_IMPLEMENTED",
   "NOT_AUTHORITATIVE",
   "CONTINUE",
   NULL,
};
static char *ETAG_options[] = { 
   "OPT_NONE",
   "OPT_INDEXES",
   "OPT_INCLUDES",
   "OPT_SYM_LINKS",
   "OPT_EXECCGI",
   "OPT_UNSET",
   "OPT_INCNOEXEC",
   "OPT_SYM_OWNER",
   "OPT_MULTI",
   "OPT_ALL",
   NULL,
};
static char *ETAG_response[] = { 
   "OK",
   "DECLINED",
   "DONE",
   "NOT_FOUND",
   "FORBIDDEN",
   "AUTH_REQUIRED",
   "SERVER_ERROR",
   "DOCUMENT_FOLLOWS",
   "MOVED",
   "REDIRECT",
   "USE_LOCAL_COPY",
   "BAD_REQUEST",
   "BAD_GATEWAY",
   "RESPONSE_CODES",
   "NOT_IMPLEMENTED",
   "NOT_AUTHORITATIVE",
   "CONTINUE",
   NULL,
};
static char **export_tags(char *tag) {
   switch (*tag) {
	case 'c':
	if(strEQ("config", tag))
	   return ETAG_config;
	if(strEQ("common", tag))
	   return ETAG_common;
	case 'h':
	if(strEQ("http", tag))
	   return ETAG_http;
	case 'm':
	if(strEQ("methods", tag))
	   return ETAG_methods;
	case 'o':
	if(strEQ("options", tag))
	   return ETAG_options;
	case 'r':
	if(strEQ("remotehost", tag))
	   return ETAG_remotehost;
	if(strEQ("response_codes", tag))
	   return ETAG_response_codes;
	if(strEQ("response", tag))
	   return ETAG_response;
	case 's':
	if(strEQ("satisfy", tag))
	   return ETAG_satisfy;
	if(strEQ("server", tag))
	   return ETAG_server;
	case 't':
	if(strEQ("types", tag))
	   return ETAG_types;
	default:
	croak("unknown tag `%s'", tag);
   }
}
