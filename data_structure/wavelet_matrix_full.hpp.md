---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/wavelet_matrix_full.hpp\"\n#include <bits/stdc++.h>\n\
    \nenum { NOTFOUND = 0xFFFFFFFFFFFFFFFFLLU };\n\nclass SuccinctBitVector {\n private:\n\
    \  const uint64_t size;  // \u30D3\u30C3\u30C8\u30D9\u30AF\u30C8\u30EB\u306E\u30B5\
    \u30A4\u30BA\n  static const uint32_t blockBitNum = 16;\n  static const uint32_t\
    \ LEVEL_L = 512;\n  static const uint32_t LEVEL_S = 16;\n\n  std::vector<uint64_t>\
    \ L;  // \u5927\u30D6\u30ED\u30C3\u30AF\n  std::vector<uint16_t> S;  // \u5C0F\
    \u30D6\u30ED\u30C3\u30AF\n  std::vector<uint16_t> B;  // \u30D3\u30C3\u30C8\u30D9\
    \u30AF\u30C8\u30EB\n\n  uint64_t numOne = 0;  // 1bit\u306E\u6570\n\n public:\n\
    \  explicit SuccinctBitVector(const uint64_t n) : size(n) {\n    const uint64_t\
    \ s =\n        (n + blockBitNum - 1) / blockBitNum + 1;  // ceil(n, blockSize)\n\
    \    this->B.assign(s, 0);\n    this->L.assign(n / LEVEL_L + 1, 0);\n    this->S.assign(n\
    \ / LEVEL_S + 1, 0);\n  }\n\n  // B[pos] = bit\n  void setBit(const uint64_t bit,\
    \ const uint64_t pos) {\n    assert(bit == 0 or bit == 1);\n    assert(pos < this->size);\n\
    \n    const uint64_t blockPos = pos / blockBitNum;\n    const uint64_t offset\
    \ = pos % blockBitNum;\n    if (bit == 1) {\n      B.at(blockPos) |= (1LLU <<\
    \ offset);\n    } else {\n      B.at(blockPos) &= (~(1LLU << offset));\n    }\n\
    \  }\n\n  // B[pos]\n  uint64_t access(const uint64_t pos) {\n    assert(pos <\
    \ this->size);\n    const uint64_t blockPos = pos / blockBitNum;\n    const uint64_t\
    \ offset = pos % blockBitNum;\n    return ((B.at(blockPos) >> offset) & 1);\n\
    \  }\n\n  void build() {\n    uint64_t num = 0;\n    for (uint64_t i = 0; i <=\
    \ size; i++) {\n      if (i % LEVEL_L == 0) {\n        L.at(i / LEVEL_L) = num;\n\
    \      }\n      if (i % LEVEL_S == 0) {\n        S.at(i / LEVEL_S) = num - L.at(i\
    \ / LEVEL_L);\n      }\n      if (i != size and i % blockBitNum == 0) {\n    \
    \    num += this->popCount(this->B.at(i / blockBitNum));\n      }\n    }\n   \
    \ this->numOne = num;\n  }\n\n  // B[0, pos)\u306Ebit\u306E\u6570\n  uint64_t\
    \ rank(const uint64_t bit, const uint64_t pos) {\n    assert(bit == 0 or bit ==\
    \ 1);\n    assert(pos <= this->size);\n\n    if (bit) {\n      return L[pos /\
    \ LEVEL_L] + S[pos / LEVEL_S] +\n             popCount(B[pos / blockBitNum] &\
    \ ((1 << (pos % blockBitNum)) - 1));\n    } else {\n      return pos - rank(1,\
    \ pos);\n    }\n  }\n\n  // rank\u756A\u76EE\u306Ebit\u306E\u4F4D\u7F6E + 1(rank\u306F\
    1-origin)\n  uint64_t select(const uint64_t bit, const uint64_t rank) {\n    assert(bit\
    \ == 0 or bit == 1);\n    assert(rank > 0);\n    if (bit == 0 and rank > this->size\
    \ - this->numOne) {\n      return NOTFOUND;\n    }\n    if (bit == 1 and rank\
    \ > this->numOne) {\n      return NOTFOUND;\n    }\n\n    // \u5927\u30D6\u30ED\
    \u30C3\u30AFL\u5185\u3092\u691C\u7D22\n    uint64_t large_idx = 0;\n    {\n  \
    \    uint64_t left = 0;\n      uint64_t right = L.size();\n      while (right\
    \ - left > 1) {\n        uint64_t mid = (left + right) / 2;\n        uint64_t\
    \ r = L.at(mid);\n        r = (bit) ? r : mid * LEVEL_L - L.at(mid);\n\n     \
    \   if (r < rank) {\n          left = mid;\n          large_idx = mid;\n     \
    \   } else {\n          right = mid;\n        }\n      }\n    }\n\n    // \u5C0F\
    \u30D6\u30ED\u30C3\u30AFS\u5185\u3092\u691C\u7D22\n    uint64_t small_idx = (large_idx\
    \ * LEVEL_L) / LEVEL_S;\n    {\n      uint64_t left = (large_idx * LEVEL_L) /\
    \ LEVEL_S;\n      uint64_t right =\n          std::min(((large_idx + 1) * LEVEL_L)\
    \ / LEVEL_S, S.size());\n      while (right - left > 1) {\n        uint64_t mid\
    \ = (left + right) / 2;\n        uint64_t r = L.at(large_idx) + S.at(mid);\n \
    \       r = (bit) ? r : mid * LEVEL_S - r;\n\n        if (r < rank) {\n      \
    \    left = mid;\n          small_idx = mid;\n        } else {\n          right\
    \ = mid;\n        }\n      }\n    }\n\n    // B\u3092\u30D6\u30ED\u30C3\u30AF\u5358\
    \u4F4D\u3067\u9806\u756A\u306B\u63A2\u7D22\n    uint64_t rank_pos = 0;\n    {\n\
    \      const uint64_t begin_block_idx = (small_idx * LEVEL_S) / blockBitNum;\n\
    \      uint64_t total_bit = L.at(large_idx) + S.at(small_idx);\n      if (bit\
    \ == 0) {\n        total_bit = small_idx * LEVEL_S - total_bit;\n      }\n   \
    \   for (uint64_t i = 0;; ++i) {\n        uint64_t b = popCount(B.at(begin_block_idx\
    \ + i));\n        if (bit == 0) {\n          b = blockBitNum - b;\n        }\n\
    \        if (total_bit + b >= rank) {\n          uint64_t block =\n          \
    \    (bit) ? B.at(begin_block_idx + i) : ~B.at(begin_block_idx + i);\n       \
    \   rank_pos = (begin_block_idx + i) * blockBitNum +\n                     selectInBlock(block,\
    \ rank - total_bit);\n          break;\n        }\n        total_bit += b;\n \
    \     }\n    }\n\n    return rank_pos + 1;\n  }\n\n  uint64_t getNumOne() const\
    \ { return numOne; }\n\n  void debug() {\n    std::cout << \"LEVEL_L(\" << L.size()\
    \ << \")\" << std::endl;\n    for (uint64_t i = 0; i < L.size(); ++i) {\n    \
    \  std::cout << L.at(i) << \", \";\n    }\n    std::cout << std::endl;\n    std::cout\
    \ << \"LEVEL_S(\" << S.size() << \")\" << std::endl;\n    for (uint64_t i = 0;\
    \ i < S.size(); ++i) {\n      std::cout << S.at(i) << \", \";\n    }\n    std::cout\
    \ << std::endl;\n  }\n\n private:\n  uint64_t popCount(uint64_t x) {\n    x =\
    \ (x & 0x5555555555555555ULL) + ((x >> 1) & 0x5555555555555555ULL);\n    x = (x\
    \ & 0x3333333333333333ULL) + ((x >> 2) & 0x3333333333333333ULL);\n    x = (x +\
    \ (x >> 4)) & 0x0f0f0f0f0f0f0f0fULL;\n    x = x + (x >> 8);\n    x = x + (x >>\
    \ 16);\n    x = x + (x >> 32);\n    return x & 0x7FLLU;\n  }\n\n  uint64_t selectInBlock(uint64_t\
    \ x, uint64_t rank) {\n    uint64_t x1 = x - ((x & 0xAAAAAAAAAAAAAAAALLU) >> 1);\n\
    \    uint64_t x2 =\n        (x1 & 0x3333333333333333LLU) + ((x1 >> 2) & 0x3333333333333333LLU);\n\
    \    uint64_t x3 = (x2 + (x2 >> 4)) & 0x0F0F0F0F0F0F0F0FLLU;\n\n    uint64_t pos\
    \ = 0;\n    for (;; pos += 8) {\n      uint64_t rank_next = (x3 >> pos) & 0xFFLLU;\n\
    \      if (rank <= rank_next) break;\n      rank -= rank_next;\n    }\n\n    uint64_t\
    \ v2 = (x2 >> pos) & 0xFLLU;\n    if (rank > v2) {\n      rank -= v2;\n      pos\
    \ += 4;\n    }\n\n    uint64_t v1 = (x1 >> pos) & 0x3LLU;\n    if (rank > v1)\
    \ {\n      rank -= v1;\n      pos += 2;\n    }\n\n    uint64_t v0 = (x >> pos)\
    \ & 0x1LLU;\n    if (v0 < rank) {\n      rank -= v0;\n      pos += 1;\n    }\n\
    \n    return pos;\n  }\n};\n\nclass WaveletMatrix {\n private:\n  std::vector<SuccinctBitVector>\
    \ bit_arrays;\n  std::vector<uint64_t> begin_one;  // \u5404bit\u306B\u7740\u76EE\
    \u3057\u305F\u3068\u304D\u306E1\u306E\u958B\u59CB\u4F4D\u7F6E\n  std::map<uint64_t,\
    \ uint64_t>\n      begin_alphabet;  // \u6700\u5F8C\u306E\u30BD\u30FC\u30C8\u3055\
    \u308C\u305F\u914D\u5217\u3067\u5404\u6587\u5B57\u306E\u958B\u59CB\u4F4D\u7F6E\
    \n  std::vector<std::vector<uint64_t>>\n      cumulative_sum;  // \u5404bit\u306B\
    \u7740\u76EE\u3057\u305F\u3068\u304D\u306E\u7D2F\u7A4D\u548C\n\n  uint64_t size;\
    \             // \u4E0E\u3048\u3089\u308C\u305F\u914D\u5217\u306E\u30B5\u30A4\u30BA\
    \n  uint64_t maximum_element;  // \u6587\u5B57\u6570\n  uint64_t bit_size;   \
    \      // \u6587\u5B57\u3092\u8868\u3059\u306E\u306B\u5FC5\u8981\u306Abit\u6570\
    \n\n public:\n  WaveletMatrix(const std::vector<uint64_t> &array) {\n    assert(array.size()\
    \ > 0);\n    size = array.size();\n    maximum_element = *max_element(array.begin(),\
    \ array.end()) + 1;\n    bit_size = get_num_of_bit(maximum_element);\n    if (bit_size\
    \ == 0) {\n      bit_size = 1;\n    }\n\n    for (uint64_t i = 0; i < bit_size;\
    \ ++i) {\n      SuccinctBitVector sv(size);\n      bit_arrays.push_back(sv);\n\
    \    }\n    this->begin_one.resize(bit_size);\n    this->cumulative_sum.resize(bit_size\
    \ + 1,\n                                std::vector<uint64_t>(size + 1, 0));\n\
    \n    for (uint64_t j = 0; j < array.size(); ++j) {\n      this->cumulative_sum.at(0).at(j\
    \ + 1) =\n          this->cumulative_sum.at(0).at(j) + array[j];\n    }\n\n  \
    \  std::vector<uint64_t> v(array);\n    for (uint64_t i = 0; i < bit_size; ++i)\
    \ {\n      std::vector<uint64_t> temp;\n      // 0\u3092temp\u306B\u3044\u308C\
    \u3066\u304F\n      for (uint64_t j = 0; j < v.size(); ++j) {\n        uint64_t\
    \ c = v.at(j);\n        uint64_t bit = (c >> (bit_size - i - 1)) & 1;  // \u3000\
    \u4E0A\u304B\u3089i\u756A\u76EE\u306Ebit\n        if (bit == 0) {\n          temp.push_back(c);\n\
    \          bit_arrays.at(i).setBit(0, j);\n        }\n      }\n\n      this->begin_one.at(i)\
    \ = temp.size();\n\n      // 1\u3092temp\u306B\u3044\u308C\u3066\u304F\n     \
    \ for (uint64_t j = 0; j < v.size(); ++j) {\n        uint64_t c = v.at(j);\n \
    \       uint64_t bit = (c >> (bit_size - i - 1)) & 1;  // \u3000\u4E0A\u304B\u3089\
    i\u756A\u76EE\u306Ebit\n        if (bit == 1) {\n          temp.push_back(c);\n\
    \          bit_arrays.at(i).setBit(1, j);\n        }\n      }\n\n      for (uint64_t\
    \ j = 0; j < temp.size(); ++j) {\n        this->cumulative_sum.at(i + 1).at(j\
    \ + 1) =\n            this->cumulative_sum.at(i + 1).at(j) + temp.at(j);\n   \
    \   }\n\n      bit_arrays.at(i).build();\n      v = temp;\n    }\n\n    // \u30BD\
    \u30FC\u30C8\u3055\u308C\u305F\u914D\u5217\u5185\u3067\u306E\u5404\u6587\u5B57\
    \u306E\u4F4D\u7F6E\u3092\u53D6\u5F97\n    for (int i = v.size() - 1; i >= 0; --i)\
    \ {\n      this->begin_alphabet[v.at(i)] = i;\n    }\n  }\n\n  // v[pos]\n  uint64_t\
    \ access(uint64_t pos) {\n    if (pos >= this->size) {\n      return NOTFOUND;\n\
    \    }\n\n    uint64_t c = 0;\n    for (uint64_t i = 0; i < bit_arrays.size();\
    \ ++i) {\n      uint64_t bit = bit_arrays.at(i).access(pos);  // \u3082\u3068\u306E\
    \u6570\u5024\u304C\u306Ei\u756A\u76EE\u306Ebit\n      c = (c <<= 1) | bit;\n \
    \     pos = bit_arrays.at(i).rank(bit, pos);\n      if (bit) {\n        pos +=\
    \ this->begin_one.at(i);\n      }\n    }\n    return c;\n  }\n\n  // i\u756A\u76EE\
    \u306Ec\u306E\u4F4D\u7F6E + 1\u3092\u8FD4\u3059\u3002rank\u306F1-origin\n  uint64_t\
    \ select(uint64_t c, uint64_t rank) {\n    assert(rank > 0);\n    if (c >= maximum_element)\
    \ {\n      return NOTFOUND;\n    }\n    if (this->begin_alphabet.find(c) == this->begin_alphabet.end())\
    \ {\n      return NOTFOUND;\n    }\n\n    uint64_t index = this->begin_alphabet.at(c)\
    \ + rank;\n    for (uint64_t i = 0; i < bit_arrays.size(); ++i) {\n      uint64_t\
    \ bit = ((c >> i) & 1);  // \u4E0B\u304B\u3089i\u756A\u76EE\u306Ebit\n      if\
    \ (bit == 1) {\n        index -= this->begin_one.at(bit_size - i - 1);\n     \
    \ }\n      index = this->bit_arrays.at(bit_size - i - 1).select(bit, index);\n\
    \    }\n    return index;\n  }\n\n  // v[begin_pos, end_pos)\u3067\u6700\u5927\
    \u5024\u306Eindex\u3092\u8FD4\u3059\n  uint64_t maxRange(uint64_t begin_pos, uint64_t\
    \ end_pos) {\n    return quantileRange(begin_pos, end_pos, end_pos - begin_pos\
    \ - 1);\n  }\n\n  // v[begin_pos, end_pos)\u3067\u6700\u5C0F\u5024\u306Eindex\u3092\
    \u8FD4\u3059\n  uint64_t minRange(uint64_t begin_pos, uint64_t end_pos) {\n  \
    \  return quantileRange(begin_pos, end_pos, 0);\n  }\n\n  // v[begin_pos, end_pos)\u3067\
    k\u756A\u76EE\u306B\u5C0F\u3055\u3044\u6570\u5024\u306Eindex\u3092\u8FD4\u3059\
    (k\u306F0-origin)\n  // \u3064\u307E\u308A\u5C0F\u3055\u3044\u9806\u306B\u4E26\
    \u3079\u3066k\u756A\u76EE\u306E\u5024\n  uint64_t quantileRange(uint64_t begin_pos,\
    \ uint64_t end_pos, uint64_t k) {\n    if ((end_pos > size || begin_pos >= end_pos)\
    \ ||\n        (k >= end_pos - begin_pos)) {\n      return NOTFOUND;\n    }\n\n\
    \    uint64_t val = 0;\n    for (uint64_t i = 0; i < bit_size; ++i) {\n      const\
    \ uint64_t num_of_zero_begin = bit_arrays.at(i).rank(0, begin_pos);\n      const\
    \ uint64_t num_of_zero_end = bit_arrays.at(i).rank(0, end_pos);\n      const uint64_t\
    \ num_of_zero =\n          num_of_zero_end - num_of_zero_begin;  // begin\u304B\
    \u3089end\u307E\u3067\u306B\u3042\u308B0\u306E\u6570\n      const uint64_t bit\
    \ =\n          (k < num_of_zero) ? 0 : 1;  // k\u756A\u76EE\u306E\u5024\u306E\u4E0A\
    \u304B\u3089i\u756A\u76EE\u306Ebit\u304C0\u304B1\u304B\n\n      if (bit) {\n \
    \       k -= num_of_zero;\n        begin_pos = this->begin_one.at(i) + begin_pos\
    \ - num_of_zero_begin;\n        end_pos = this->begin_one.at(i) + end_pos - num_of_zero_end;\n\
    \      } else {\n        begin_pos = num_of_zero_begin;\n        end_pos = num_of_zero_begin\
    \ + num_of_zero;\n      }\n\n      val = ((val << 1) | bit);\n    }\n\n    uint64_t\
    \ left = 0;\n    for (uint64_t i = 0; i < bit_size; ++i) {\n      const uint64_t\
    \ bit = (val >> (bit_size - i - 1)) & 1;  // \u4E0A\u304B\u3089i\u756A\u76EE\u306E\
    bit\n      left = bit_arrays.at(i).rank(bit, left);  // c\u306Ei\u756A\u76EE\u306E\
    bit\u3068\u540C\u3058\u6570\u5024\u306E\u6570\n      if (bit) {\n        left\
    \ += this->begin_one.at(i);\n      }\n    }\n\n    const uint64_t rank = begin_pos\
    \ + k - left + 1;\n    return select(val, rank) - 1;\n  }\n\n  // v[0, pos)\u306E\
    c\u306E\u6570\n  uint64_t rank(uint64_t c, uint64_t pos) {\n    assert(pos < size);\n\
    \    if (c >= maximum_element) {\n      return 0;\n    }\n    if (this->begin_alphabet.find(c)\
    \ == this->begin_alphabet.end()) {\n      return 0;\n    }\n\n    for (uint64_t\
    \ i = 0; i < bit_size; ++i) {\n      uint64_t bit = (c >> (bit_size - i - 1))\
    \ & 1;  // \u4E0A\u304B\u3089i\u756A\u76EE\u306Ebit\n      pos = bit_arrays.at(i).rank(bit,\
    \ pos);  // c\u306Ei\u756A\u76EE\u306Ebit\u3068\u540C\u3058\u6570\u5024\u306E\u6570\
    \n      if (bit) {\n        pos += this->begin_one.at(i);\n      }\n    }\n\n\
    \    uint64_t begin_pos = this->begin_alphabet.at(c);\n    return pos - begin_pos;\n\
    \  }\n\n  // v[begin_pos, end_pos)\u3067[min, max)\u306B\u5165\u308B\u5024\u306E\
    \u500B\u6570\n  uint64_t rangeFreq(uint64_t begin_pos, uint64_t end_pos, uint64_t\
    \ min_c,\n                     uint64_t max_c) {\n    if ((end_pos > size || begin_pos\
    \ >= end_pos) || (min_c >= max_c) ||\n        min_c >= maximum_element) {\n  \
    \    return 0;\n    }\n\n    const auto maxi_t = rankAll(max_c, begin_pos, end_pos);\n\
    \    const auto mini_t = rankAll(min_c, begin_pos, end_pos);\n    return std::get<1>(maxi_t)\
    \ - std::get<1>(mini_t);\n  }\n\n  // v[0, pos)\u3067c\u3088\u308A\u5C0F\u3055\
    \u3044\u6587\u5B57\u306E\u6570\n  uint64_t rankLessThan(uint64_t c, uint64_t begin,\
    \ uint64_t end) {\n    auto t = rankAll(c, begin, end);\n    return std::get<1>(t);\n\
    \  }\n\n  // v[0, pos)\u3067c\u3088\u308A\u5927\u304D\u3044\u6587\u5B57\u306E\u6570\
    \n  uint64_t rankMoreThan(uint64_t c, uint64_t begin, uint64_t end) {\n    auto\
    \ t = rankAll(c, begin, end);\n    return std::get<2>(t);\n  }\n\n  // v[begin,\n\
    \  // end)\u3067(c\u3068\u540C\u3058\u5024\u306E\u6570\u3001c\u3088\u308A\u5C0F\
    \u3055\u3044\u5024\u306E\u6570\u3001c\u3088\u308A\u5927\u304D\u3044\u5024\u306E\
    \u6570)\u3092\u6C42\u3081\u308B\n  std::tuple<uint64_t, uint64_t, uint64_t> rankAll(const\
    \ uint64_t c,\n                                                   uint64_t begin,\n\
    \                                                   uint64_t end) {\n    assert(end\
    \ <= size);\n    const uint64_t num = end - begin;\n\n    if (begin >= end) {\n\
    \      return std::make_tuple(0, 0, 0);\n    }\n    if (c >= maximum_element ||\
    \ end == 0) {\n      return std::make_tuple(0, num, 0);\n    }\n\n    uint64_t\
    \ rank_less_than = 0, rank_more_than = 0;\n    for (size_t i = 0; i < bit_size\
    \ && begin < end; ++i) {\n      const uint64_t bit = (c >> (bit_size - i - 1))\
    \ & 1;\n\n      const uint64_t rank0_begin = this->bit_arrays.at(i).rank(0, begin);\n\
    \      const uint64_t rank0_end = this->bit_arrays.at(i).rank(0, end);\n     \
    \ const uint64_t rank1_begin = begin - rank0_begin;\n      const uint64_t rank1_end\
    \ = end - rank0_end;\n\n      if (bit) {\n        rank_less_than +=\n        \
    \    (rank0_end - rank0_begin);  // i\u756A\u76EE\u306Ebit\u304C0\u306E\u3082\u306E\
    \u306F\u9664\u5916\u3055\u308C\u308B\n        begin = this->begin_one.at(i) +\
    \ rank1_begin;\n        end = this->begin_one.at(i) + rank1_end;\n      } else\
    \ {\n        rank_more_than +=\n            (rank1_end - rank1_begin);  // i\u756A\
    \u76EE\u306Ebit\u304C1\u306E\u3082\u306E\u306F\u9664\u5916\u3055\u308C\u308B\n\
    \        begin = rank0_begin;\n        end = rank0_end;\n      }\n    }\n\n  \
    \  const uint64_t rank = num - rank_less_than - rank_more_than;\n    return std::make_tuple(rank,\
    \ rank_less_than, rank_more_than);\n  }\n\n  // T[s, e)\u3067\u51FA\u73FE\u56DE\
    \u6570\u304C\u591A\u3044\u9806\u306Bk\u500B\u306E(\u5024\uFF0C\u983B\u5EA6)\u3092\
    \u8FD4\u3059\n  // \u983B\u5EA6\u304C\u540C\u3058\u5834\u5408\u306F\u5024\u304C\
    \u5C0F\u3055\u3044\u3082\u306E\u304C\u512A\u5148\u3055\u308C\u308B\n  std::vector<std::pair<uint64_t,\
    \ uint64_t>> topk(uint64_t s, uint64_t e,\n                                  \
    \                uint64_t k) {\n    assert(s < e);\n    std::vector<std::pair<uint64_t,\
    \ uint64_t>> result;\n\n    // (\u983B\u5EA6\uFF0C\u6DF1\u3055\uFF0C\u5024)\u306E\
    \u9806\u3067\u30BD\u30FC\u30C8\n    auto c =\n        [](const std::tuple<uint64_t,\
    \ uint64_t, uint64_t, uint64_t, uint64_t>\n               &l,\n           const\
    \ std::tuple<uint64_t, uint64_t, uint64_t, uint64_t, uint64_t>\n             \
    \  &r) {\n          // width\n          if (std::get<0>(l) != std::get<0>(r))\
    \ {\n            return std::get<0>(l) < std::get<0>(r);\n          }\n      \
    \    // depth\n          if (std::get<3>(l) != std::get<3>(r)) {\n           \
    \ return std::get<3>(l) > std::get<3>(r);\n          }\n          // value\n \
    \         if (std::get<4>(l) != std::get<4>(r)) {\n            return std::get<4>(l)\
    \ > std::get<4>(r);\n          }\n          return true;\n        };\n\n    std::priority_queue<\n\
    \        std::tuple<uint64_t, uint64_t, uint64_t, uint64_t, uint64_t>,\n     \
    \   std::vector<\n            std::tuple<uint64_t, uint64_t, uint64_t, uint64_t,\
    \ uint64_t>>,\n        decltype(c)>\n        que(c);  // width, left, right, depth,\
    \ value\n    que.push(std::make_tuple(e - s, s, e, 0, 0));\n\n    while (not que.empty())\
    \ {\n      auto element = que.top();\n      que.pop();\n      uint64_t width,\
    \ left, right, depth, value;\n      std::tie(width, left, right, depth, value)\
    \ = element;\n\n      if (depth >= this->bit_size) {\n        result.emplace_back(std::make_pair(value,\
    \ right - left));\n        if (result.size() >= k) {\n          break;\n     \
    \   }\n        continue;\n      }\n\n      // 0\n      const uint64_t left0 =\
    \ this->bit_arrays.at(depth).rank(0, left);\n      const uint64_t right0 = this->bit_arrays.at(depth).rank(0,\
    \ right);\n      if (left0 < right0) {\n        que.push(\n            std::make_tuple(right0\
    \ - left0, left0, right0, depth + 1, value));\n      }\n\n      // 1\n      const\
    \ uint64_t left1 =\n          this->begin_one.at(depth) + this->bit_arrays.at(depth).rank(1,\
    \ left);\n      const uint64_t right1 =\n          this->begin_one.at(depth) +\
    \ this->bit_arrays.at(depth).rank(1, right);\n      if (left1 < right1) {\n  \
    \      que.push(std::make_tuple(right1 - left1, left1, right1, depth + 1,\n  \
    \                               value | (1 << (bit_size - depth - 1))));\n   \
    \   }\n    }\n\n    return result;\n  };\n\n  // T[begin_pos, end_pos)\u3067x\
    \ <= c < y\u3092\u6E80\u305F\u3059c\u306E\u548C\u3092\u8FD4\u3059\n  uint64_t\
    \ rangeSum(const uint64_t begin, const uint64_t end, const uint64_t x,\n     \
    \               const uint64_t y) {\n    return rangeSum(begin, end, 0, 0, x,\
    \ y);\n  }\n\n  // T[begin_pos, end_pos)\u3067x <= c < y\u3092\u6E80\u305F\u3059\
    \u6700\u5927\u306Ec\u3092\u8FD4\u3059\n  uint64_t prevValue(const uint64_t begin_pos,\
    \ const uint64_t end_pos,\n                     const uint64_t x, uint64_t y)\
    \ {\n    assert(end_pos <= size);\n    const uint64_t num = end_pos - begin_pos;\n\
    \n    if (x >= y or y == 0) {\n      return NOTFOUND;\n    }\n    if (y > maximum_element)\
    \ {\n      y = maximum_element;\n    }\n\n    if (begin_pos >= end_pos) {\n  \
    \    return NOTFOUND;\n    }\n    if (x >= maximum_element || end_pos == 0) {\n\
    \      return NOTFOUND;\n    }\n\n    y--;  // x <= c <= y\u306B\u3059\u308B\n\
    \n    std::stack<std::tuple<uint64_t, uint64_t, uint64_t, uint64_t, bool>>\n \
    \       s;  // (begin, end, depth, c, tight)\n    s.emplace(std::make_tuple(begin_pos,\
    \ end_pos, 0, 0, true));\n\n    while (not s.empty()) {\n      uint64_t b, e,\
    \ depth, c;\n      bool tight;\n      std::tie(b, e, depth, c, tight) = s.top();\n\
    \      s.pop();\n\n      if (depth == bit_size) {\n        if (c >= x) {\n   \
    \       return c;\n        }\n        continue;\n      }\n\n      const uint64_t\
    \ bit = (y >> (bit_size - depth - 1)) & 1;\n\n      const uint64_t rank0_begin\
    \ = this->bit_arrays.at(depth).rank(0, b);\n      const uint64_t rank0_end = this->bit_arrays.at(depth).rank(0,\
    \ e);\n      const uint64_t rank1_begin = b - rank0_begin;\n      const uint64_t\
    \ rank1_end = e - rank0_end;\n\n      // d\u756A\u76EE\u306Ebit\u304C0\u306E\u3082\
    \u306E\u3092\u4F7F\u3046\n      const uint64_t b0 = rank0_begin;\n      const\
    \ uint64_t e0 = rank0_end;\n      if (b0 != e0) {  // \u7BC4\u56F2\u304C\u3064\
    \u3076\u308C\u3066\u306A\u3044\n        const uint64_t c0 = ((c << 1) | 0);\n\
    \        s.emplace(std::make_tuple(b0, e0, depth + 1, c0, tight and bit == 0));\n\
    \      }\n\n      // d\u756A\u76EE\u306Ebit\u304C1\u306E\u3082\u306E\u3092\u4F7F\
    \u3046\n      const uint64_t b1 = this->begin_one.at(depth) + rank1_begin;\n \
    \     const uint64_t e1 = this->begin_one.at(depth) + rank1_end;\n      if (b1\
    \ != e1) {\n        if (not tight or bit == 1) {\n          const auto c1 = ((c\
    \ << 1) | 1);\n          s.emplace(std::make_tuple(b1, e1, depth + 1, c1, tight));\n\
    \        }\n      }\n    }\n\n    return NOTFOUND;\n  }\n\n  // T[begin_pos, end_pos)\u3067\
    x <= c < y\u3092\u6E80\u305F\u3059\u6700\u5C0F\u306Ec\u3092\u8FD4\u3059\n  uint64_t\
    \ nextValue(const uint64_t begin_pos, const uint64_t end_pos,\n              \
    \       const uint64_t x, const uint64_t y) {\n    assert(end_pos <= size);\n\
    \    const uint64_t num = end_pos - begin_pos;\n\n    if (x >= y or y == 0) {\n\
    \      return NOTFOUND;\n    }\n\n    if (begin_pos >= end_pos) {\n      return\
    \ NOTFOUND;\n    }\n    if (x >= maximum_element || end_pos == 0) {\n      return\
    \ NOTFOUND;\n    }\n\n    std::stack<std::tuple<uint64_t, uint64_t, uint64_t,\
    \ uint64_t, bool>>\n        s;  // (begin, end, depth, c, tight)\n    s.emplace(std::make_tuple(begin_pos,\
    \ end_pos, 0, 0, true));\n\n    while (not s.empty()) {\n      uint64_t b, e,\
    \ depth, c;\n      bool tight;\n      std::tie(b, e, depth, c, tight) = s.top();\n\
    \      s.pop();\n\n      if (depth == bit_size) {\n        if (c < y) {\n    \
    \      return c;\n        }\n        continue;\n      }\n\n      const uint64_t\
    \ bit = (x >> (bit_size - depth - 1)) & 1;\n\n      const uint64_t rank0_begin\
    \ = this->bit_arrays.at(depth).rank(0, b);\n      const uint64_t rank0_end = this->bit_arrays.at(depth).rank(0,\
    \ e);\n      const uint64_t rank1_begin = b - rank0_begin;\n      const uint64_t\
    \ rank1_end = e - rank0_end;\n\n      // d\u756A\u76EE\u306Ebit\u304C1\u306E\u3082\
    \u306E\u3092\u4F7F\u3046\n      const uint64_t b1 = this->begin_one.at(depth)\
    \ + rank1_begin;\n      const uint64_t e1 = this->begin_one.at(depth) + rank1_end;\n\
    \      if (b1 != e1) {\n        const auto c1 = ((c << 1) | 1);\n        s.emplace(std::make_tuple(b1,\
    \ e1, depth + 1, c1, tight and bit == 1));\n      }\n\n      // d\u756A\u76EE\u306E\
    bit\u304C0\u306E\u3082\u306E\u3092\u4F7F\u3046\n      const uint64_t b0 = rank0_begin;\n\
    \      const uint64_t e0 = rank0_end;\n      if (b0 != e0) {\n        if (not\
    \ tight or bit == 0) {\n          const uint64_t c0 = ((c << 1) | 0);\n      \
    \    s.emplace(std::make_tuple(b0, e0, depth + 1, c0, tight));\n        }\n  \
    \    }\n    }\n\n    return NOTFOUND;\n  }\n\n  // T[s1, e1)\u3068T[s2, e2)\u306B\
    \u5171\u901A\u3057\u3066\u51FA\u73FE\u3059\u308B\u8981\u7D20\u3092\u6C42\u3081\
    \u308B\n  std::vector<std::tuple<uint64_t, uint64_t, uint64_t>> intersect(\n \
    \     uint64_t _s1, uint64_t _e1, uint64_t _s2, uint64_t _e2) {\n    assert(_s1\
    \ < _e1);\n    assert(_s2 < _e2);\n\n    std::vector<std::tuple<uint64_t, uint64_t,\
    \ uint64_t>> intersection;\n\n    std::queue<\n        std::tuple<uint64_t, uint64_t,\
    \ uint64_t, uint64_t, uint64_t, uint64_t>>\n        que;  // s1, e1, s2, e2, depth,\
    \ value\n    que.push(std::make_tuple(_s1, _e1, _s2, _e2, 0, 0));\n    while (not\
    \ que.empty()) {\n      auto e = que.front();\n      que.pop();\n      uint64_t\
    \ s1, e1, s2, e2, depth, value;\n      std::tie(s1, e1, s2, e2, depth, value)\
    \ = e;\n\n      if (depth >= this->bit_size) {\n        intersection.emplace_back(std::make_tuple(value,\
    \ e1 - s1, e2 - s2));\n        continue;\n      }\n\n      // 0\n      uint64_t\
    \ s1_0 = this->bit_arrays.at(depth).rank(0, s1);\n      uint64_t e1_0 = this->bit_arrays.at(depth).rank(0,\
    \ e1);\n      uint64_t s2_0 = this->bit_arrays.at(depth).rank(0, s2);\n      uint64_t\
    \ e2_0 = this->bit_arrays.at(depth).rank(0, e2);\n\n      if (s1_0 != e1_0 and\
    \ s2_0 != e2_0) {\n        que.push(std::make_tuple(s1_0, e1_0, s2_0, e2_0, depth\
    \ + 1, value));\n      }\n\n      // 1\n      uint64_t s1_1 =\n          this->begin_one.at(depth)\
    \ + this->bit_arrays.at(depth).rank(1, s1);\n      uint64_t e1_1 =\n         \
    \ this->begin_one.at(depth) + this->bit_arrays.at(depth).rank(1, e1);\n      uint64_t\
    \ s2_1 =\n          this->begin_one.at(depth) + this->bit_arrays.at(depth).rank(1,\
    \ s2);\n      uint64_t e2_1 =\n          this->begin_one.at(depth) + this->bit_arrays.at(depth).rank(1,\
    \ e2);\n\n      if (s1_1 != e1_1 and s2_1 != e2_1) {\n        que.push(std::make_tuple(s1_1,\
    \ e1_1, s2_1, e2_1, depth + 1,\n                                 value | (1 <<\
    \ bit_size - depth - 1)));\n      }\n    }\n\n    return intersection;\n  };\n\
    \n private:\n  uint64_t get_num_of_bit(uint64_t x) {\n    if (x == 0) return 0;\n\
    \    x--;\n    uint64_t bit_num = 0;\n    while (x >> bit_num) {\n      ++bit_num;\n\
    \    }\n    return bit_num;\n  }\n\n  uint64_t rangeSum(const uint64_t begin,\
    \ const uint64_t end,\n                    const uint64_t depth, const uint64_t\
    \ c, const uint64_t x,\n                    const uint64_t y) {\n    if (begin\
    \ == end) {\n      return 0;\n    }\n\n    if (depth == bit_size) {\n      if\
    \ (x <= c and c < y) {\n        return c * (end - begin);  // \u5024 * \u983B\u5EA6\
    \n      }\n      return 0;\n    }\n\n    const uint64_t next_c = ((uint64_t)1\
    \ << (bit_size - depth - 1)) |\n                            c;  // \u4E0A\u304B\
    \u3089depth\u756A\u76EE\u306Ebit\u3092\u7ACB\u3066\u308B\n    const uint64_t all_one_c\
    \ =\n        (((uint64_t)1 << (bit_size - depth - 1)) - 1) |\n        next_c;\
    \  // depth\u4EE5\u964D\u306Ebit\u3092\u305F\u3066\u308B(\u3053\u308C\u4EE5\u964D\
    \u5168\u90E81\u3092\u9078\u3093\u3060\u3068\u304D\u306E\u5024)\n    if (all_one_c\
    \ < x or y <= c) {\n      return 0;\n    }\n\n    // [begin, pos)\u306E\u3059\u3079\
    \u3066\u306E\u8981\u7D20\u306F[x, y)\n    if (x <= c and all_one_c < y) {\n  \
    \    return this->cumulative_sum.at(depth).at(end) -\n             this->cumulative_sum.at(depth).at(begin);\n\
    \    }\n\n    const uint64_t rank0_begin = this->bit_arrays.at(depth).rank(0,\
    \ begin);\n    const uint64_t rank0_end = this->bit_arrays.at(depth).rank(0, end);\n\
    \    const uint64_t rank1_begin = begin - rank0_begin;\n    const uint64_t rank1_end\
    \ = end - rank0_end;\n\n    return rangeSum(rank0_begin, rank0_end, depth + 1,\
    \ c, x, y) +\n           rangeSum(this->begin_one.at(depth) + rank1_begin,\n \
    \                   this->begin_one[depth] + rank1_end, depth + 1, next_c, x,\n\
    \                    y);\n  }\n};\n"
  code: "#include <bits/stdc++.h>\n\nenum { NOTFOUND = 0xFFFFFFFFFFFFFFFFLLU };\n\n\
    class SuccinctBitVector {\n private:\n  const uint64_t size;  // \u30D3\u30C3\u30C8\
    \u30D9\u30AF\u30C8\u30EB\u306E\u30B5\u30A4\u30BA\n  static const uint32_t blockBitNum\
    \ = 16;\n  static const uint32_t LEVEL_L = 512;\n  static const uint32_t LEVEL_S\
    \ = 16;\n\n  std::vector<uint64_t> L;  // \u5927\u30D6\u30ED\u30C3\u30AF\n  std::vector<uint16_t>\
    \ S;  // \u5C0F\u30D6\u30ED\u30C3\u30AF\n  std::vector<uint16_t> B;  // \u30D3\
    \u30C3\u30C8\u30D9\u30AF\u30C8\u30EB\n\n  uint64_t numOne = 0;  // 1bit\u306E\u6570\
    \n\n public:\n  explicit SuccinctBitVector(const uint64_t n) : size(n) {\n   \
    \ const uint64_t s =\n        (n + blockBitNum - 1) / blockBitNum + 1;  // ceil(n,\
    \ blockSize)\n    this->B.assign(s, 0);\n    this->L.assign(n / LEVEL_L + 1, 0);\n\
    \    this->S.assign(n / LEVEL_S + 1, 0);\n  }\n\n  // B[pos] = bit\n  void setBit(const\
    \ uint64_t bit, const uint64_t pos) {\n    assert(bit == 0 or bit == 1);\n   \
    \ assert(pos < this->size);\n\n    const uint64_t blockPos = pos / blockBitNum;\n\
    \    const uint64_t offset = pos % blockBitNum;\n    if (bit == 1) {\n      B.at(blockPos)\
    \ |= (1LLU << offset);\n    } else {\n      B.at(blockPos) &= (~(1LLU << offset));\n\
    \    }\n  }\n\n  // B[pos]\n  uint64_t access(const uint64_t pos) {\n    assert(pos\
    \ < this->size);\n    const uint64_t blockPos = pos / blockBitNum;\n    const\
    \ uint64_t offset = pos % blockBitNum;\n    return ((B.at(blockPos) >> offset)\
    \ & 1);\n  }\n\n  void build() {\n    uint64_t num = 0;\n    for (uint64_t i =\
    \ 0; i <= size; i++) {\n      if (i % LEVEL_L == 0) {\n        L.at(i / LEVEL_L)\
    \ = num;\n      }\n      if (i % LEVEL_S == 0) {\n        S.at(i / LEVEL_S) =\
    \ num - L.at(i / LEVEL_L);\n      }\n      if (i != size and i % blockBitNum ==\
    \ 0) {\n        num += this->popCount(this->B.at(i / blockBitNum));\n      }\n\
    \    }\n    this->numOne = num;\n  }\n\n  // B[0, pos)\u306Ebit\u306E\u6570\n\
    \  uint64_t rank(const uint64_t bit, const uint64_t pos) {\n    assert(bit ==\
    \ 0 or bit == 1);\n    assert(pos <= this->size);\n\n    if (bit) {\n      return\
    \ L[pos / LEVEL_L] + S[pos / LEVEL_S] +\n             popCount(B[pos / blockBitNum]\
    \ & ((1 << (pos % blockBitNum)) - 1));\n    } else {\n      return pos - rank(1,\
    \ pos);\n    }\n  }\n\n  // rank\u756A\u76EE\u306Ebit\u306E\u4F4D\u7F6E + 1(rank\u306F\
    1-origin)\n  uint64_t select(const uint64_t bit, const uint64_t rank) {\n    assert(bit\
    \ == 0 or bit == 1);\n    assert(rank > 0);\n    if (bit == 0 and rank > this->size\
    \ - this->numOne) {\n      return NOTFOUND;\n    }\n    if (bit == 1 and rank\
    \ > this->numOne) {\n      return NOTFOUND;\n    }\n\n    // \u5927\u30D6\u30ED\
    \u30C3\u30AFL\u5185\u3092\u691C\u7D22\n    uint64_t large_idx = 0;\n    {\n  \
    \    uint64_t left = 0;\n      uint64_t right = L.size();\n      while (right\
    \ - left > 1) {\n        uint64_t mid = (left + right) / 2;\n        uint64_t\
    \ r = L.at(mid);\n        r = (bit) ? r : mid * LEVEL_L - L.at(mid);\n\n     \
    \   if (r < rank) {\n          left = mid;\n          large_idx = mid;\n     \
    \   } else {\n          right = mid;\n        }\n      }\n    }\n\n    // \u5C0F\
    \u30D6\u30ED\u30C3\u30AFS\u5185\u3092\u691C\u7D22\n    uint64_t small_idx = (large_idx\
    \ * LEVEL_L) / LEVEL_S;\n    {\n      uint64_t left = (large_idx * LEVEL_L) /\
    \ LEVEL_S;\n      uint64_t right =\n          std::min(((large_idx + 1) * LEVEL_L)\
    \ / LEVEL_S, S.size());\n      while (right - left > 1) {\n        uint64_t mid\
    \ = (left + right) / 2;\n        uint64_t r = L.at(large_idx) + S.at(mid);\n \
    \       r = (bit) ? r : mid * LEVEL_S - r;\n\n        if (r < rank) {\n      \
    \    left = mid;\n          small_idx = mid;\n        } else {\n          right\
    \ = mid;\n        }\n      }\n    }\n\n    // B\u3092\u30D6\u30ED\u30C3\u30AF\u5358\
    \u4F4D\u3067\u9806\u756A\u306B\u63A2\u7D22\n    uint64_t rank_pos = 0;\n    {\n\
    \      const uint64_t begin_block_idx = (small_idx * LEVEL_S) / blockBitNum;\n\
    \      uint64_t total_bit = L.at(large_idx) + S.at(small_idx);\n      if (bit\
    \ == 0) {\n        total_bit = small_idx * LEVEL_S - total_bit;\n      }\n   \
    \   for (uint64_t i = 0;; ++i) {\n        uint64_t b = popCount(B.at(begin_block_idx\
    \ + i));\n        if (bit == 0) {\n          b = blockBitNum - b;\n        }\n\
    \        if (total_bit + b >= rank) {\n          uint64_t block =\n          \
    \    (bit) ? B.at(begin_block_idx + i) : ~B.at(begin_block_idx + i);\n       \
    \   rank_pos = (begin_block_idx + i) * blockBitNum +\n                     selectInBlock(block,\
    \ rank - total_bit);\n          break;\n        }\n        total_bit += b;\n \
    \     }\n    }\n\n    return rank_pos + 1;\n  }\n\n  uint64_t getNumOne() const\
    \ { return numOne; }\n\n  void debug() {\n    std::cout << \"LEVEL_L(\" << L.size()\
    \ << \")\" << std::endl;\n    for (uint64_t i = 0; i < L.size(); ++i) {\n    \
    \  std::cout << L.at(i) << \", \";\n    }\n    std::cout << std::endl;\n    std::cout\
    \ << \"LEVEL_S(\" << S.size() << \")\" << std::endl;\n    for (uint64_t i = 0;\
    \ i < S.size(); ++i) {\n      std::cout << S.at(i) << \", \";\n    }\n    std::cout\
    \ << std::endl;\n  }\n\n private:\n  uint64_t popCount(uint64_t x) {\n    x =\
    \ (x & 0x5555555555555555ULL) + ((x >> 1) & 0x5555555555555555ULL);\n    x = (x\
    \ & 0x3333333333333333ULL) + ((x >> 2) & 0x3333333333333333ULL);\n    x = (x +\
    \ (x >> 4)) & 0x0f0f0f0f0f0f0f0fULL;\n    x = x + (x >> 8);\n    x = x + (x >>\
    \ 16);\n    x = x + (x >> 32);\n    return x & 0x7FLLU;\n  }\n\n  uint64_t selectInBlock(uint64_t\
    \ x, uint64_t rank) {\n    uint64_t x1 = x - ((x & 0xAAAAAAAAAAAAAAAALLU) >> 1);\n\
    \    uint64_t x2 =\n        (x1 & 0x3333333333333333LLU) + ((x1 >> 2) & 0x3333333333333333LLU);\n\
    \    uint64_t x3 = (x2 + (x2 >> 4)) & 0x0F0F0F0F0F0F0F0FLLU;\n\n    uint64_t pos\
    \ = 0;\n    for (;; pos += 8) {\n      uint64_t rank_next = (x3 >> pos) & 0xFFLLU;\n\
    \      if (rank <= rank_next) break;\n      rank -= rank_next;\n    }\n\n    uint64_t\
    \ v2 = (x2 >> pos) & 0xFLLU;\n    if (rank > v2) {\n      rank -= v2;\n      pos\
    \ += 4;\n    }\n\n    uint64_t v1 = (x1 >> pos) & 0x3LLU;\n    if (rank > v1)\
    \ {\n      rank -= v1;\n      pos += 2;\n    }\n\n    uint64_t v0 = (x >> pos)\
    \ & 0x1LLU;\n    if (v0 < rank) {\n      rank -= v0;\n      pos += 1;\n    }\n\
    \n    return pos;\n  }\n};\n\nclass WaveletMatrix {\n private:\n  std::vector<SuccinctBitVector>\
    \ bit_arrays;\n  std::vector<uint64_t> begin_one;  // \u5404bit\u306B\u7740\u76EE\
    \u3057\u305F\u3068\u304D\u306E1\u306E\u958B\u59CB\u4F4D\u7F6E\n  std::map<uint64_t,\
    \ uint64_t>\n      begin_alphabet;  // \u6700\u5F8C\u306E\u30BD\u30FC\u30C8\u3055\
    \u308C\u305F\u914D\u5217\u3067\u5404\u6587\u5B57\u306E\u958B\u59CB\u4F4D\u7F6E\
    \n  std::vector<std::vector<uint64_t>>\n      cumulative_sum;  // \u5404bit\u306B\
    \u7740\u76EE\u3057\u305F\u3068\u304D\u306E\u7D2F\u7A4D\u548C\n\n  uint64_t size;\
    \             // \u4E0E\u3048\u3089\u308C\u305F\u914D\u5217\u306E\u30B5\u30A4\u30BA\
    \n  uint64_t maximum_element;  // \u6587\u5B57\u6570\n  uint64_t bit_size;   \
    \      // \u6587\u5B57\u3092\u8868\u3059\u306E\u306B\u5FC5\u8981\u306Abit\u6570\
    \n\n public:\n  WaveletMatrix(const std::vector<uint64_t> &array) {\n    assert(array.size()\
    \ > 0);\n    size = array.size();\n    maximum_element = *max_element(array.begin(),\
    \ array.end()) + 1;\n    bit_size = get_num_of_bit(maximum_element);\n    if (bit_size\
    \ == 0) {\n      bit_size = 1;\n    }\n\n    for (uint64_t i = 0; i < bit_size;\
    \ ++i) {\n      SuccinctBitVector sv(size);\n      bit_arrays.push_back(sv);\n\
    \    }\n    this->begin_one.resize(bit_size);\n    this->cumulative_sum.resize(bit_size\
    \ + 1,\n                                std::vector<uint64_t>(size + 1, 0));\n\
    \n    for (uint64_t j = 0; j < array.size(); ++j) {\n      this->cumulative_sum.at(0).at(j\
    \ + 1) =\n          this->cumulative_sum.at(0).at(j) + array[j];\n    }\n\n  \
    \  std::vector<uint64_t> v(array);\n    for (uint64_t i = 0; i < bit_size; ++i)\
    \ {\n      std::vector<uint64_t> temp;\n      // 0\u3092temp\u306B\u3044\u308C\
    \u3066\u304F\n      for (uint64_t j = 0; j < v.size(); ++j) {\n        uint64_t\
    \ c = v.at(j);\n        uint64_t bit = (c >> (bit_size - i - 1)) & 1;  // \u3000\
    \u4E0A\u304B\u3089i\u756A\u76EE\u306Ebit\n        if (bit == 0) {\n          temp.push_back(c);\n\
    \          bit_arrays.at(i).setBit(0, j);\n        }\n      }\n\n      this->begin_one.at(i)\
    \ = temp.size();\n\n      // 1\u3092temp\u306B\u3044\u308C\u3066\u304F\n     \
    \ for (uint64_t j = 0; j < v.size(); ++j) {\n        uint64_t c = v.at(j);\n \
    \       uint64_t bit = (c >> (bit_size - i - 1)) & 1;  // \u3000\u4E0A\u304B\u3089\
    i\u756A\u76EE\u306Ebit\n        if (bit == 1) {\n          temp.push_back(c);\n\
    \          bit_arrays.at(i).setBit(1, j);\n        }\n      }\n\n      for (uint64_t\
    \ j = 0; j < temp.size(); ++j) {\n        this->cumulative_sum.at(i + 1).at(j\
    \ + 1) =\n            this->cumulative_sum.at(i + 1).at(j) + temp.at(j);\n   \
    \   }\n\n      bit_arrays.at(i).build();\n      v = temp;\n    }\n\n    // \u30BD\
    \u30FC\u30C8\u3055\u308C\u305F\u914D\u5217\u5185\u3067\u306E\u5404\u6587\u5B57\
    \u306E\u4F4D\u7F6E\u3092\u53D6\u5F97\n    for (int i = v.size() - 1; i >= 0; --i)\
    \ {\n      this->begin_alphabet[v.at(i)] = i;\n    }\n  }\n\n  // v[pos]\n  uint64_t\
    \ access(uint64_t pos) {\n    if (pos >= this->size) {\n      return NOTFOUND;\n\
    \    }\n\n    uint64_t c = 0;\n    for (uint64_t i = 0; i < bit_arrays.size();\
    \ ++i) {\n      uint64_t bit = bit_arrays.at(i).access(pos);  // \u3082\u3068\u306E\
    \u6570\u5024\u304C\u306Ei\u756A\u76EE\u306Ebit\n      c = (c <<= 1) | bit;\n \
    \     pos = bit_arrays.at(i).rank(bit, pos);\n      if (bit) {\n        pos +=\
    \ this->begin_one.at(i);\n      }\n    }\n    return c;\n  }\n\n  // i\u756A\u76EE\
    \u306Ec\u306E\u4F4D\u7F6E + 1\u3092\u8FD4\u3059\u3002rank\u306F1-origin\n  uint64_t\
    \ select(uint64_t c, uint64_t rank) {\n    assert(rank > 0);\n    if (c >= maximum_element)\
    \ {\n      return NOTFOUND;\n    }\n    if (this->begin_alphabet.find(c) == this->begin_alphabet.end())\
    \ {\n      return NOTFOUND;\n    }\n\n    uint64_t index = this->begin_alphabet.at(c)\
    \ + rank;\n    for (uint64_t i = 0; i < bit_arrays.size(); ++i) {\n      uint64_t\
    \ bit = ((c >> i) & 1);  // \u4E0B\u304B\u3089i\u756A\u76EE\u306Ebit\n      if\
    \ (bit == 1) {\n        index -= this->begin_one.at(bit_size - i - 1);\n     \
    \ }\n      index = this->bit_arrays.at(bit_size - i - 1).select(bit, index);\n\
    \    }\n    return index;\n  }\n\n  // v[begin_pos, end_pos)\u3067\u6700\u5927\
    \u5024\u306Eindex\u3092\u8FD4\u3059\n  uint64_t maxRange(uint64_t begin_pos, uint64_t\
    \ end_pos) {\n    return quantileRange(begin_pos, end_pos, end_pos - begin_pos\
    \ - 1);\n  }\n\n  // v[begin_pos, end_pos)\u3067\u6700\u5C0F\u5024\u306Eindex\u3092\
    \u8FD4\u3059\n  uint64_t minRange(uint64_t begin_pos, uint64_t end_pos) {\n  \
    \  return quantileRange(begin_pos, end_pos, 0);\n  }\n\n  // v[begin_pos, end_pos)\u3067\
    k\u756A\u76EE\u306B\u5C0F\u3055\u3044\u6570\u5024\u306Eindex\u3092\u8FD4\u3059\
    (k\u306F0-origin)\n  // \u3064\u307E\u308A\u5C0F\u3055\u3044\u9806\u306B\u4E26\
    \u3079\u3066k\u756A\u76EE\u306E\u5024\n  uint64_t quantileRange(uint64_t begin_pos,\
    \ uint64_t end_pos, uint64_t k) {\n    if ((end_pos > size || begin_pos >= end_pos)\
    \ ||\n        (k >= end_pos - begin_pos)) {\n      return NOTFOUND;\n    }\n\n\
    \    uint64_t val = 0;\n    for (uint64_t i = 0; i < bit_size; ++i) {\n      const\
    \ uint64_t num_of_zero_begin = bit_arrays.at(i).rank(0, begin_pos);\n      const\
    \ uint64_t num_of_zero_end = bit_arrays.at(i).rank(0, end_pos);\n      const uint64_t\
    \ num_of_zero =\n          num_of_zero_end - num_of_zero_begin;  // begin\u304B\
    \u3089end\u307E\u3067\u306B\u3042\u308B0\u306E\u6570\n      const uint64_t bit\
    \ =\n          (k < num_of_zero) ? 0 : 1;  // k\u756A\u76EE\u306E\u5024\u306E\u4E0A\
    \u304B\u3089i\u756A\u76EE\u306Ebit\u304C0\u304B1\u304B\n\n      if (bit) {\n \
    \       k -= num_of_zero;\n        begin_pos = this->begin_one.at(i) + begin_pos\
    \ - num_of_zero_begin;\n        end_pos = this->begin_one.at(i) + end_pos - num_of_zero_end;\n\
    \      } else {\n        begin_pos = num_of_zero_begin;\n        end_pos = num_of_zero_begin\
    \ + num_of_zero;\n      }\n\n      val = ((val << 1) | bit);\n    }\n\n    uint64_t\
    \ left = 0;\n    for (uint64_t i = 0; i < bit_size; ++i) {\n      const uint64_t\
    \ bit = (val >> (bit_size - i - 1)) & 1;  // \u4E0A\u304B\u3089i\u756A\u76EE\u306E\
    bit\n      left = bit_arrays.at(i).rank(bit, left);  // c\u306Ei\u756A\u76EE\u306E\
    bit\u3068\u540C\u3058\u6570\u5024\u306E\u6570\n      if (bit) {\n        left\
    \ += this->begin_one.at(i);\n      }\n    }\n\n    const uint64_t rank = begin_pos\
    \ + k - left + 1;\n    return select(val, rank) - 1;\n  }\n\n  // v[0, pos)\u306E\
    c\u306E\u6570\n  uint64_t rank(uint64_t c, uint64_t pos) {\n    assert(pos < size);\n\
    \    if (c >= maximum_element) {\n      return 0;\n    }\n    if (this->begin_alphabet.find(c)\
    \ == this->begin_alphabet.end()) {\n      return 0;\n    }\n\n    for (uint64_t\
    \ i = 0; i < bit_size; ++i) {\n      uint64_t bit = (c >> (bit_size - i - 1))\
    \ & 1;  // \u4E0A\u304B\u3089i\u756A\u76EE\u306Ebit\n      pos = bit_arrays.at(i).rank(bit,\
    \ pos);  // c\u306Ei\u756A\u76EE\u306Ebit\u3068\u540C\u3058\u6570\u5024\u306E\u6570\
    \n      if (bit) {\n        pos += this->begin_one.at(i);\n      }\n    }\n\n\
    \    uint64_t begin_pos = this->begin_alphabet.at(c);\n    return pos - begin_pos;\n\
    \  }\n\n  // v[begin_pos, end_pos)\u3067[min, max)\u306B\u5165\u308B\u5024\u306E\
    \u500B\u6570\n  uint64_t rangeFreq(uint64_t begin_pos, uint64_t end_pos, uint64_t\
    \ min_c,\n                     uint64_t max_c) {\n    if ((end_pos > size || begin_pos\
    \ >= end_pos) || (min_c >= max_c) ||\n        min_c >= maximum_element) {\n  \
    \    return 0;\n    }\n\n    const auto maxi_t = rankAll(max_c, begin_pos, end_pos);\n\
    \    const auto mini_t = rankAll(min_c, begin_pos, end_pos);\n    return std::get<1>(maxi_t)\
    \ - std::get<1>(mini_t);\n  }\n\n  // v[0, pos)\u3067c\u3088\u308A\u5C0F\u3055\
    \u3044\u6587\u5B57\u306E\u6570\n  uint64_t rankLessThan(uint64_t c, uint64_t begin,\
    \ uint64_t end) {\n    auto t = rankAll(c, begin, end);\n    return std::get<1>(t);\n\
    \  }\n\n  // v[0, pos)\u3067c\u3088\u308A\u5927\u304D\u3044\u6587\u5B57\u306E\u6570\
    \n  uint64_t rankMoreThan(uint64_t c, uint64_t begin, uint64_t end) {\n    auto\
    \ t = rankAll(c, begin, end);\n    return std::get<2>(t);\n  }\n\n  // v[begin,\n\
    \  // end)\u3067(c\u3068\u540C\u3058\u5024\u306E\u6570\u3001c\u3088\u308A\u5C0F\
    \u3055\u3044\u5024\u306E\u6570\u3001c\u3088\u308A\u5927\u304D\u3044\u5024\u306E\
    \u6570)\u3092\u6C42\u3081\u308B\n  std::tuple<uint64_t, uint64_t, uint64_t> rankAll(const\
    \ uint64_t c,\n                                                   uint64_t begin,\n\
    \                                                   uint64_t end) {\n    assert(end\
    \ <= size);\n    const uint64_t num = end - begin;\n\n    if (begin >= end) {\n\
    \      return std::make_tuple(0, 0, 0);\n    }\n    if (c >= maximum_element ||\
    \ end == 0) {\n      return std::make_tuple(0, num, 0);\n    }\n\n    uint64_t\
    \ rank_less_than = 0, rank_more_than = 0;\n    for (size_t i = 0; i < bit_size\
    \ && begin < end; ++i) {\n      const uint64_t bit = (c >> (bit_size - i - 1))\
    \ & 1;\n\n      const uint64_t rank0_begin = this->bit_arrays.at(i).rank(0, begin);\n\
    \      const uint64_t rank0_end = this->bit_arrays.at(i).rank(0, end);\n     \
    \ const uint64_t rank1_begin = begin - rank0_begin;\n      const uint64_t rank1_end\
    \ = end - rank0_end;\n\n      if (bit) {\n        rank_less_than +=\n        \
    \    (rank0_end - rank0_begin);  // i\u756A\u76EE\u306Ebit\u304C0\u306E\u3082\u306E\
    \u306F\u9664\u5916\u3055\u308C\u308B\n        begin = this->begin_one.at(i) +\
    \ rank1_begin;\n        end = this->begin_one.at(i) + rank1_end;\n      } else\
    \ {\n        rank_more_than +=\n            (rank1_end - rank1_begin);  // i\u756A\
    \u76EE\u306Ebit\u304C1\u306E\u3082\u306E\u306F\u9664\u5916\u3055\u308C\u308B\n\
    \        begin = rank0_begin;\n        end = rank0_end;\n      }\n    }\n\n  \
    \  const uint64_t rank = num - rank_less_than - rank_more_than;\n    return std::make_tuple(rank,\
    \ rank_less_than, rank_more_than);\n  }\n\n  // T[s, e)\u3067\u51FA\u73FE\u56DE\
    \u6570\u304C\u591A\u3044\u9806\u306Bk\u500B\u306E(\u5024\uFF0C\u983B\u5EA6)\u3092\
    \u8FD4\u3059\n  // \u983B\u5EA6\u304C\u540C\u3058\u5834\u5408\u306F\u5024\u304C\
    \u5C0F\u3055\u3044\u3082\u306E\u304C\u512A\u5148\u3055\u308C\u308B\n  std::vector<std::pair<uint64_t,\
    \ uint64_t>> topk(uint64_t s, uint64_t e,\n                                  \
    \                uint64_t k) {\n    assert(s < e);\n    std::vector<std::pair<uint64_t,\
    \ uint64_t>> result;\n\n    // (\u983B\u5EA6\uFF0C\u6DF1\u3055\uFF0C\u5024)\u306E\
    \u9806\u3067\u30BD\u30FC\u30C8\n    auto c =\n        [](const std::tuple<uint64_t,\
    \ uint64_t, uint64_t, uint64_t, uint64_t>\n               &l,\n           const\
    \ std::tuple<uint64_t, uint64_t, uint64_t, uint64_t, uint64_t>\n             \
    \  &r) {\n          // width\n          if (std::get<0>(l) != std::get<0>(r))\
    \ {\n            return std::get<0>(l) < std::get<0>(r);\n          }\n      \
    \    // depth\n          if (std::get<3>(l) != std::get<3>(r)) {\n           \
    \ return std::get<3>(l) > std::get<3>(r);\n          }\n          // value\n \
    \         if (std::get<4>(l) != std::get<4>(r)) {\n            return std::get<4>(l)\
    \ > std::get<4>(r);\n          }\n          return true;\n        };\n\n    std::priority_queue<\n\
    \        std::tuple<uint64_t, uint64_t, uint64_t, uint64_t, uint64_t>,\n     \
    \   std::vector<\n            std::tuple<uint64_t, uint64_t, uint64_t, uint64_t,\
    \ uint64_t>>,\n        decltype(c)>\n        que(c);  // width, left, right, depth,\
    \ value\n    que.push(std::make_tuple(e - s, s, e, 0, 0));\n\n    while (not que.empty())\
    \ {\n      auto element = que.top();\n      que.pop();\n      uint64_t width,\
    \ left, right, depth, value;\n      std::tie(width, left, right, depth, value)\
    \ = element;\n\n      if (depth >= this->bit_size) {\n        result.emplace_back(std::make_pair(value,\
    \ right - left));\n        if (result.size() >= k) {\n          break;\n     \
    \   }\n        continue;\n      }\n\n      // 0\n      const uint64_t left0 =\
    \ this->bit_arrays.at(depth).rank(0, left);\n      const uint64_t right0 = this->bit_arrays.at(depth).rank(0,\
    \ right);\n      if (left0 < right0) {\n        que.push(\n            std::make_tuple(right0\
    \ - left0, left0, right0, depth + 1, value));\n      }\n\n      // 1\n      const\
    \ uint64_t left1 =\n          this->begin_one.at(depth) + this->bit_arrays.at(depth).rank(1,\
    \ left);\n      const uint64_t right1 =\n          this->begin_one.at(depth) +\
    \ this->bit_arrays.at(depth).rank(1, right);\n      if (left1 < right1) {\n  \
    \      que.push(std::make_tuple(right1 - left1, left1, right1, depth + 1,\n  \
    \                               value | (1 << (bit_size - depth - 1))));\n   \
    \   }\n    }\n\n    return result;\n  };\n\n  // T[begin_pos, end_pos)\u3067x\
    \ <= c < y\u3092\u6E80\u305F\u3059c\u306E\u548C\u3092\u8FD4\u3059\n  uint64_t\
    \ rangeSum(const uint64_t begin, const uint64_t end, const uint64_t x,\n     \
    \               const uint64_t y) {\n    return rangeSum(begin, end, 0, 0, x,\
    \ y);\n  }\n\n  // T[begin_pos, end_pos)\u3067x <= c < y\u3092\u6E80\u305F\u3059\
    \u6700\u5927\u306Ec\u3092\u8FD4\u3059\n  uint64_t prevValue(const uint64_t begin_pos,\
    \ const uint64_t end_pos,\n                     const uint64_t x, uint64_t y)\
    \ {\n    assert(end_pos <= size);\n    const uint64_t num = end_pos - begin_pos;\n\
    \n    if (x >= y or y == 0) {\n      return NOTFOUND;\n    }\n    if (y > maximum_element)\
    \ {\n      y = maximum_element;\n    }\n\n    if (begin_pos >= end_pos) {\n  \
    \    return NOTFOUND;\n    }\n    if (x >= maximum_element || end_pos == 0) {\n\
    \      return NOTFOUND;\n    }\n\n    y--;  // x <= c <= y\u306B\u3059\u308B\n\
    \n    std::stack<std::tuple<uint64_t, uint64_t, uint64_t, uint64_t, bool>>\n \
    \       s;  // (begin, end, depth, c, tight)\n    s.emplace(std::make_tuple(begin_pos,\
    \ end_pos, 0, 0, true));\n\n    while (not s.empty()) {\n      uint64_t b, e,\
    \ depth, c;\n      bool tight;\n      std::tie(b, e, depth, c, tight) = s.top();\n\
    \      s.pop();\n\n      if (depth == bit_size) {\n        if (c >= x) {\n   \
    \       return c;\n        }\n        continue;\n      }\n\n      const uint64_t\
    \ bit = (y >> (bit_size - depth - 1)) & 1;\n\n      const uint64_t rank0_begin\
    \ = this->bit_arrays.at(depth).rank(0, b);\n      const uint64_t rank0_end = this->bit_arrays.at(depth).rank(0,\
    \ e);\n      const uint64_t rank1_begin = b - rank0_begin;\n      const uint64_t\
    \ rank1_end = e - rank0_end;\n\n      // d\u756A\u76EE\u306Ebit\u304C0\u306E\u3082\
    \u306E\u3092\u4F7F\u3046\n      const uint64_t b0 = rank0_begin;\n      const\
    \ uint64_t e0 = rank0_end;\n      if (b0 != e0) {  // \u7BC4\u56F2\u304C\u3064\
    \u3076\u308C\u3066\u306A\u3044\n        const uint64_t c0 = ((c << 1) | 0);\n\
    \        s.emplace(std::make_tuple(b0, e0, depth + 1, c0, tight and bit == 0));\n\
    \      }\n\n      // d\u756A\u76EE\u306Ebit\u304C1\u306E\u3082\u306E\u3092\u4F7F\
    \u3046\n      const uint64_t b1 = this->begin_one.at(depth) + rank1_begin;\n \
    \     const uint64_t e1 = this->begin_one.at(depth) + rank1_end;\n      if (b1\
    \ != e1) {\n        if (not tight or bit == 1) {\n          const auto c1 = ((c\
    \ << 1) | 1);\n          s.emplace(std::make_tuple(b1, e1, depth + 1, c1, tight));\n\
    \        }\n      }\n    }\n\n    return NOTFOUND;\n  }\n\n  // T[begin_pos, end_pos)\u3067\
    x <= c < y\u3092\u6E80\u305F\u3059\u6700\u5C0F\u306Ec\u3092\u8FD4\u3059\n  uint64_t\
    \ nextValue(const uint64_t begin_pos, const uint64_t end_pos,\n              \
    \       const uint64_t x, const uint64_t y) {\n    assert(end_pos <= size);\n\
    \    const uint64_t num = end_pos - begin_pos;\n\n    if (x >= y or y == 0) {\n\
    \      return NOTFOUND;\n    }\n\n    if (begin_pos >= end_pos) {\n      return\
    \ NOTFOUND;\n    }\n    if (x >= maximum_element || end_pos == 0) {\n      return\
    \ NOTFOUND;\n    }\n\n    std::stack<std::tuple<uint64_t, uint64_t, uint64_t,\
    \ uint64_t, bool>>\n        s;  // (begin, end, depth, c, tight)\n    s.emplace(std::make_tuple(begin_pos,\
    \ end_pos, 0, 0, true));\n\n    while (not s.empty()) {\n      uint64_t b, e,\
    \ depth, c;\n      bool tight;\n      std::tie(b, e, depth, c, tight) = s.top();\n\
    \      s.pop();\n\n      if (depth == bit_size) {\n        if (c < y) {\n    \
    \      return c;\n        }\n        continue;\n      }\n\n      const uint64_t\
    \ bit = (x >> (bit_size - depth - 1)) & 1;\n\n      const uint64_t rank0_begin\
    \ = this->bit_arrays.at(depth).rank(0, b);\n      const uint64_t rank0_end = this->bit_arrays.at(depth).rank(0,\
    \ e);\n      const uint64_t rank1_begin = b - rank0_begin;\n      const uint64_t\
    \ rank1_end = e - rank0_end;\n\n      // d\u756A\u76EE\u306Ebit\u304C1\u306E\u3082\
    \u306E\u3092\u4F7F\u3046\n      const uint64_t b1 = this->begin_one.at(depth)\
    \ + rank1_begin;\n      const uint64_t e1 = this->begin_one.at(depth) + rank1_end;\n\
    \      if (b1 != e1) {\n        const auto c1 = ((c << 1) | 1);\n        s.emplace(std::make_tuple(b1,\
    \ e1, depth + 1, c1, tight and bit == 1));\n      }\n\n      // d\u756A\u76EE\u306E\
    bit\u304C0\u306E\u3082\u306E\u3092\u4F7F\u3046\n      const uint64_t b0 = rank0_begin;\n\
    \      const uint64_t e0 = rank0_end;\n      if (b0 != e0) {\n        if (not\
    \ tight or bit == 0) {\n          const uint64_t c0 = ((c << 1) | 0);\n      \
    \    s.emplace(std::make_tuple(b0, e0, depth + 1, c0, tight));\n        }\n  \
    \    }\n    }\n\n    return NOTFOUND;\n  }\n\n  // T[s1, e1)\u3068T[s2, e2)\u306B\
    \u5171\u901A\u3057\u3066\u51FA\u73FE\u3059\u308B\u8981\u7D20\u3092\u6C42\u3081\
    \u308B\n  std::vector<std::tuple<uint64_t, uint64_t, uint64_t>> intersect(\n \
    \     uint64_t _s1, uint64_t _e1, uint64_t _s2, uint64_t _e2) {\n    assert(_s1\
    \ < _e1);\n    assert(_s2 < _e2);\n\n    std::vector<std::tuple<uint64_t, uint64_t,\
    \ uint64_t>> intersection;\n\n    std::queue<\n        std::tuple<uint64_t, uint64_t,\
    \ uint64_t, uint64_t, uint64_t, uint64_t>>\n        que;  // s1, e1, s2, e2, depth,\
    \ value\n    que.push(std::make_tuple(_s1, _e1, _s2, _e2, 0, 0));\n    while (not\
    \ que.empty()) {\n      auto e = que.front();\n      que.pop();\n      uint64_t\
    \ s1, e1, s2, e2, depth, value;\n      std::tie(s1, e1, s2, e2, depth, value)\
    \ = e;\n\n      if (depth >= this->bit_size) {\n        intersection.emplace_back(std::make_tuple(value,\
    \ e1 - s1, e2 - s2));\n        continue;\n      }\n\n      // 0\n      uint64_t\
    \ s1_0 = this->bit_arrays.at(depth).rank(0, s1);\n      uint64_t e1_0 = this->bit_arrays.at(depth).rank(0,\
    \ e1);\n      uint64_t s2_0 = this->bit_arrays.at(depth).rank(0, s2);\n      uint64_t\
    \ e2_0 = this->bit_arrays.at(depth).rank(0, e2);\n\n      if (s1_0 != e1_0 and\
    \ s2_0 != e2_0) {\n        que.push(std::make_tuple(s1_0, e1_0, s2_0, e2_0, depth\
    \ + 1, value));\n      }\n\n      // 1\n      uint64_t s1_1 =\n          this->begin_one.at(depth)\
    \ + this->bit_arrays.at(depth).rank(1, s1);\n      uint64_t e1_1 =\n         \
    \ this->begin_one.at(depth) + this->bit_arrays.at(depth).rank(1, e1);\n      uint64_t\
    \ s2_1 =\n          this->begin_one.at(depth) + this->bit_arrays.at(depth).rank(1,\
    \ s2);\n      uint64_t e2_1 =\n          this->begin_one.at(depth) + this->bit_arrays.at(depth).rank(1,\
    \ e2);\n\n      if (s1_1 != e1_1 and s2_1 != e2_1) {\n        que.push(std::make_tuple(s1_1,\
    \ e1_1, s2_1, e2_1, depth + 1,\n                                 value | (1 <<\
    \ bit_size - depth - 1)));\n      }\n    }\n\n    return intersection;\n  };\n\
    \n private:\n  uint64_t get_num_of_bit(uint64_t x) {\n    if (x == 0) return 0;\n\
    \    x--;\n    uint64_t bit_num = 0;\n    while (x >> bit_num) {\n      ++bit_num;\n\
    \    }\n    return bit_num;\n  }\n\n  uint64_t rangeSum(const uint64_t begin,\
    \ const uint64_t end,\n                    const uint64_t depth, const uint64_t\
    \ c, const uint64_t x,\n                    const uint64_t y) {\n    if (begin\
    \ == end) {\n      return 0;\n    }\n\n    if (depth == bit_size) {\n      if\
    \ (x <= c and c < y) {\n        return c * (end - begin);  // \u5024 * \u983B\u5EA6\
    \n      }\n      return 0;\n    }\n\n    const uint64_t next_c = ((uint64_t)1\
    \ << (bit_size - depth - 1)) |\n                            c;  // \u4E0A\u304B\
    \u3089depth\u756A\u76EE\u306Ebit\u3092\u7ACB\u3066\u308B\n    const uint64_t all_one_c\
    \ =\n        (((uint64_t)1 << (bit_size - depth - 1)) - 1) |\n        next_c;\
    \  // depth\u4EE5\u964D\u306Ebit\u3092\u305F\u3066\u308B(\u3053\u308C\u4EE5\u964D\
    \u5168\u90E81\u3092\u9078\u3093\u3060\u3068\u304D\u306E\u5024)\n    if (all_one_c\
    \ < x or y <= c) {\n      return 0;\n    }\n\n    // [begin, pos)\u306E\u3059\u3079\
    \u3066\u306E\u8981\u7D20\u306F[x, y)\n    if (x <= c and all_one_c < y) {\n  \
    \    return this->cumulative_sum.at(depth).at(end) -\n             this->cumulative_sum.at(depth).at(begin);\n\
    \    }\n\n    const uint64_t rank0_begin = this->bit_arrays.at(depth).rank(0,\
    \ begin);\n    const uint64_t rank0_end = this->bit_arrays.at(depth).rank(0, end);\n\
    \    const uint64_t rank1_begin = begin - rank0_begin;\n    const uint64_t rank1_end\
    \ = end - rank0_end;\n\n    return rangeSum(rank0_begin, rank0_end, depth + 1,\
    \ c, x, y) +\n           rangeSum(this->begin_one.at(depth) + rank1_begin,\n \
    \                   this->begin_one[depth] + rank1_end, depth + 1, next_c, x,\n\
    \                    y);\n  }\n};"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/wavelet_matrix_full.hpp
  requiredBy: []
  timestamp: '2022-12-27 18:14:54-05:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/wavelet_matrix_full.hpp
layout: document
redirect_from:
- /library/data_structure/wavelet_matrix_full.hpp
- /library/data_structure/wavelet_matrix_full.hpp.html
title: data_structure/wavelet_matrix_full.hpp
---
