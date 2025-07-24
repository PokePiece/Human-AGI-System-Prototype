#pragma once
#define llama_token_eos 2

#ifdef __cplusplus
extern "C" {
#endif

typedef struct llama_context llama_context;

typedef struct {
    int n_ctx;
    int n_threads;
} llama_context_params;

llama_context_params llama_context_default_params(void);
llama_context* llama_init_from_file(const char* path, llama_context_params params);
void llama_free(llama_context* ctx);

int* llama_tokenize(llama_context* ctx, const char* text, bool add_bos);
int llama_eval(llama_context* ctx, const int* tokens, int n_tokens, int n_past, int n_threads);
const char* llama_token_to_str(llama_context* ctx, int token);
int llama_sample_top_p_top_k(llama_context* ctx, int top_k, float top_p, int n_batch, float temp, int repeat_penalty, const int* last_n_tokens);

#ifdef __cplusplus
}
#endif
