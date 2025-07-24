#include "CoreBrain.h"
#include <iostream>
#include "llama.h"

// Destructor frees the context
CoreBrain::~CoreBrain()
{
    if (ctx)
    {
        llama_free(ctx);
        ctx = nullptr;
    }
}

typedef int llama_n_tokens;




bool CoreBrain::loadModel(const std::string &modelPath)
{
    llama_context_params params = llama_context_default_params();
    params.n_ctx = 2048;
    params.n_threads = 4;

    ctx = llama_init_from_file(modelPath.c_str(), params);
    if (!ctx)
    {
        std::cerr << "Failed to load model from " << modelPath << std::endl;
        return false;
    }
    std::cout << "Model loaded from " << modelPath << std::endl;
    return true;
}

std::string CoreBrain::generate(const std::string &prompt, int n_predict, int n_threads)
{
    if (!ctx)
        return "";

    // Tokenize prompt
    const int *token_array = llama_tokenize(ctx, prompt.c_str(), true);
    int n_tokens = llama_n_tokens(ctx);

    std::vector<int> tokens(token_array, token_array + n_tokens);

    if (tokens.empty())
        return "";

    int n_past = 0;

    // Evaluate prompt tokens
    if (llama_eval(ctx, tokens.data(), (int)tokens.size(), n_past, n_threads) != 0)
    {
        std::cerr << "llama_eval failed" << std::endl;
        return "";
    }

    n_past += (int)tokens.size();

    std::string output;

    // Generate tokens loop
    for (int i = 0; i < n_predict; i++)
    {
        int token = llama_sample_top_p_top_k(ctx, 1, 0.95f, 40, 1.0f, 1, nullptr);
        if (token == llama_token_eos)
            break;

        output += llama_token_to_str(ctx, token);

        if (llama_eval(ctx, &token, 1, n_past, n_threads) != 0)
        {
            std::cerr << "llama_eval failed during generation" << std::endl;
            break;
        }
        n_past++;
    }

    return output;
}
