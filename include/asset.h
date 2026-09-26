#pragma once

#include <array>
#include <cstdint>
#include <string>

const std::string gtDir = ".gt";
extern std::string rootDir;

struct AssetInfo;
struct AssetOps;

enum class Asset : uint8_t {
    Blob,
    Tree,
    Index,
    Ignore,
    Config
};

enum class AssetType : uint8_t {
    Directory,
    File
};

struct AssetOps {
    bool (*validate)(const AssetInfo& asset);
    void (*create)(const AssetInfo& asset);
};

struct AssetInfo {
    Asset asset;
    const char* name;
    const char* dotExtension;
    AssetType type;

    const AssetInfo* children;
    size_t childrenCount;

    const AssetOps* ops;
};


extern const std::array<AssetInfo, 6> assets;

void setRootPath(std::string& path);
