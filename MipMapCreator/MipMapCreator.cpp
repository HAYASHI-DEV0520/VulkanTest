// MipMapCreator.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image.h>
#include <stb_image_write.h>
#include <stb_image_resize2.h>

enum class Commands {
	DEFAULT = 0,
	CONVERT = 1
};


void _CONVERT(int cmdCount, char** cmd) {
	int texWidth, texHeight, texChannels;
	stbi_uc* pixels = stbi_load(cmd[2], &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
	uint64_t imageSize = texWidth * texHeight * 4;

	if (!pixels) {
		std::cerr << "invalid file!";
		return;
	}

	uint32_t mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(texWidth, texHeight)))) + 1; // 1 for original image


	stbi_uc* endPixels = nullptr;

	for (uint32_t i = 1; i < mipLevels; i++) {

		stbi_uc* newPixels = stbir_resize_uint8_srgb(pixels, texWidth, texHeight, texWidth * 4, nullptr,
			(texWidth > 1 ? texWidth / 2 : 1), (texHeight > 1 ? texHeight / 2 : 1), (texHeight > 1 ? texHeight / 2 : 1) * 4, stbir_pixel_layout::STBIR_RGBA);

		texWidth = (texWidth > 1 ? texWidth / 2 : 1);
		texHeight = (texHeight > 1 ? texHeight / 2 : 1);

		char buf[10];
		std::sprintf(buf, "_%d.png", static_cast<int>(i));

		std::string filename = std::string(cmd[2]);
		if (filename.substr(filename.size() - 4, 4) != ".png" && filename.substr(filename.size() - 4, 4) != ".jpg") {
			std::cerr << "not jpg or png file? aborting..";
			return;
		}
		filename = filename.substr(0, filename.size() - 4);
		if (!stbi_write_png((filename + std::string(buf)).c_str(), texWidth, texHeight, 4, newPixels, texWidth * 4)) {
			std::cerr << "failed to create mipmap image file!";
			return;
		}

		free(pixels);
		pixels = newPixels;
		endPixels = newPixels;
	}
	free(endPixels);

	std::cout << mipLevels - 1 << " file(s) created" << std::endl;
}

int main(int cmdCount, char** cmd) {
	
	if (cmdCount <= 2) {
		std::cerr << "error: not enough input\n";
		return 1;
	}

	Commands status = Commands::DEFAULT;

	if (!strcmp(cmd[1], "convert")) {
		status = Commands::CONVERT;
	}

	unsigned long options = 0;
	for (int i = 3; i < cmdCount; i++) {

	}

	switch (status) {
	case Commands::CONVERT:
		_CONVERT(cmdCount, cmd);
		break;
	default:
		std::cerr << "invalid command!";
		break;
	}
	return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
