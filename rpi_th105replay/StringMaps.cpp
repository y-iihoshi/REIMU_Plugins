#include "StringMaps.h"

using namespace std;
using namespace Th105;

namespace
{
	map<uint16_t, string> CreateVersionMap()
	{
		map<uint16_t, string> versions;

#if 0
		versions[100] = "1.00";
		versions[101] = "1.01";
		versions[102] = "1.02";
		versions[103] = "1.03";
		versions[104] = "1.04 or 1.05";
		versions[105] = "1.05?";
#endif
		versions[106] = "1.06";

		return versions;
	}

	map<Mode, string> CreateModeMap()
	{
		map<Mode, string> modes;

		modes[Mode::Story          ] = "Story";
#if 0
		modes[Mode::Arcade         ] = "Arcade";
#endif
		modes[Mode::VsCom          ] = "vs COM";
		modes[Mode::VsPlayer       ] = "vs PLAYER";
		modes[Mode::VsNetworkHost  ] = "vs NETWORK （ホスト側）";
		modes[Mode::VsNetworkClient] = "vs NETWORK （クライアント側）";
		modes[Mode::VsNetworkWatch ] = "vs NETWORK （観戦）";

		return modes;
	}

	map<Chara, string> CreateCharacterMap()
	{
		map<Chara, string> characters;

		characters[Chara::Reimu    ] = "博麗 霊夢";
		characters[Chara::Marisa   ] = "霧雨 魔理沙";
		characters[Chara::Sakuya   ] = "十六夜 咲夜";
		characters[Chara::Alice    ] = "アリス・マーガトロイド";
		characters[Chara::Patchouli] = "パチュリー・ノーレッジ";
		characters[Chara::Youmu    ] = "魂魄 妖夢";
		characters[Chara::Remilia  ] = "レミリア・スカーレット";
		characters[Chara::Yuyuko   ] = "西行寺 幽々子";
		characters[Chara::Yukari   ] = "八雲 紫";
		characters[Chara::Suika    ] = "伊吹 萃香";
		characters[Chara::Reisen   ] = "鈴仙・優曇華院・イナバ";
		characters[Chara::Aya      ] = "射命丸 文";
		characters[Chara::Komachi  ] = "小野塚 小町";
		characters[Chara::Iku      ] = "永江 衣玖";
		characters[Chara::Tenshi   ] = "比那名居 天子";

		return characters;
	}

	map<uint16_t, string> CreateSystemCardMap()
	{
		map<uint16_t, string> cards;

		cards[0] = "「気質発現」";
		cards[1] = "「霊撃」";
		cards[2] = "「ガード反撃」";
		cards[3] = "「スペル増幅」";
		cards[4] = "「体力回復」";
		cards[5] = "「霊力回復」";

		return cards;
	}

	map<Chara, map<uint16_t, string>> CreateCardMap()
	{
		map<Chara, map<uint16_t, string>> cards;

		cards[Chara::Reimu][100] = "博麗アミュレット";
		cards[Chara::Reimu][101] = "警醒陣";
		cards[Chara::Reimu][102] = "亜空穴";
		cards[Chara::Reimu][103] = "昇天脚";
		cards[Chara::Reimu][104] = "妖怪バスター";
		cards[Chara::Reimu][105] = "繋縛陣";
		cards[Chara::Reimu][106] = "封魔亜空穴";
		cards[Chara::Reimu][107] = "抄地昇天脚";
		cards[Chara::Reimu][108] = "拡散アミュレット";
		cards[Chara::Reimu][109] = "常置陣";
		cards[Chara::Reimu][110] = "刹那亜空穴";
		cards[Chara::Reimu][200] = "霊符「夢想妙珠」";
		cards[Chara::Reimu][201] = "神霊「夢想封印」";
		cards[Chara::Reimu][206] = "神技「八方鬼縛陣」";
		cards[Chara::Reimu][208] = "珠符「明珠暗投」";
		cards[Chara::Reimu][209] = "宝符「陰陽宝玉」";
		cards[Chara::Reimu][210] = "宝具「陰陽鬼神玉」";
		cards[Chara::Reimu][214] = "神技「天覇風神脚」";
		cards[Chara::Reimu][219] = "「夢想天生」";
		cards[Chara::Marisa][100] = "ウィッチレイライン";
		cards[Chara::Marisa][101] = "ミアズマスウィープ";
		cards[Chara::Marisa][102] = "グラウンドスターダスト";
		cards[Chara::Marisa][103] = "メテオニックデブリ";
		cards[Chara::Marisa][104] = "ラジアルストライク";
		cards[Chara::Marisa][105] = "バスキースウィーパー";
		cards[Chara::Marisa][106] = "デビルダムトーチ";
		cards[Chara::Marisa][107] = "ナロースパーク";
		cards[Chara::Marisa][108] = "アップスウィープ";
		cards[Chara::Marisa][109] = "ステラミサイル";
		cards[Chara::Marisa][111] = "グリーンスプレッド";
		cards[Chara::Marisa][200] = "恋符「マスタースパーク」";
		cards[Chara::Marisa][202] = "魔砲「ファイナルスパーク」";
		cards[Chara::Marisa][203] = "星符「ドラゴンメテオ」";
		cards[Chara::Marisa][205] = "魔符「スターダストレヴァリエ」";
		cards[Chara::Marisa][206] = "星符「エスケープベロシティ」";
		cards[Chara::Marisa][207] = "彗星「ブレイジングスター」";
		cards[Chara::Marisa][208] = "星符「メテオニックシャワー」";
		cards[Chara::Marisa][211] = "光符「ルミネスストライク」";
		cards[Chara::Marisa][215] = "儀符「オーレリーズサン」";
		cards[Chara::Marisa][219] = "邪恋「実りやすいマスタースパーク」";
		cards[Chara::Sakuya][100] = "クロースアップマジック";
		cards[Chara::Sakuya][101] = "バウンスノーバウンス";
		cards[Chara::Sakuya][102] = "マジックスターソード";
		cards[Chara::Sakuya][103] = "バニシングエブリシング";
		cards[Chara::Sakuya][104] = "プロペリングシルバー";
		cards[Chara::Sakuya][105] = "スクウェアリコシェ";
		cards[Chara::Sakuya][106] = "離剣の見";
		cards[Chara::Sakuya][107] = "パーフェクトメイド";
		cards[Chara::Sakuya][200] = "幻符「殺人ドール」";
		cards[Chara::Sakuya][201] = "時符「プライベートスクウェア」";
		cards[Chara::Sakuya][202] = "傷符「インスクライブレッドソウル」";
		cards[Chara::Sakuya][203] = "幻葬「夜霧の幻影殺人鬼」";
		cards[Chara::Sakuya][204] = "「咲夜の世界」";
		cards[Chara::Sakuya][205] = "傷魂「ソウルスカルプチュア」";
		cards[Chara::Sakuya][206] = "銀符「シルバーバウンド」";
		cards[Chara::Sakuya][207] = "奇術「エターナルミーク」";
		cards[Chara::Sakuya][208] = "速符「ルミネスリコシェ」";
		cards[Chara::Sakuya][209] = "時符「咲夜特製ストップウォッチ」";
		cards[Chara::Alice][100] = "人形操創";
		cards[Chara::Alice][101] = "人形無操";
		cards[Chara::Alice][102] = "人形置操";
		cards[Chara::Alice][103] = "人形振起";
		cards[Chara::Alice][104] = "人形帰巣";
		cards[Chara::Alice][105] = "人形火葬";
		cards[Chara::Alice][106] = "人形千槍";
		cards[Chara::Alice][107] = "人形ＳＰ";
		cards[Chara::Alice][109] = "大江戸爆薬からくり人形";
		cards[Chara::Alice][111] = "シーカーワイヤー";
		cards[Chara::Alice][200] = "魔符「アーティフルサクリファイス」";
		cards[Chara::Alice][201] = "戦符「リトルレギオン」";
		cards[Chara::Alice][202] = "咒符「上海人形」";
		cards[Chara::Alice][203] = "魔操「リターンイナニメトネス」";
		cards[Chara::Alice][204] = "戦操「ドールズウォー」";
		cards[Chara::Alice][205] = "咒詛「蓬莱人形」";
		cards[Chara::Alice][206] = "偵符「シーカードールズ」";
		cards[Chara::Alice][207] = "紅符「和蘭人形」";
		cards[Chara::Alice][208] = "人形「未来文楽」";
		cards[Chara::Alice][209] = "注力「トリップワイヤー」";
		cards[Chara::Patchouli][100] = "サマーレッド";
		cards[Chara::Patchouli][101] = "ウィンターエレメント";
		cards[Chara::Patchouli][102] = "スプリングウィンド";
		cards[Chara::Patchouli][103] = "オータムエッジ";
		cards[Chara::Patchouli][104] = "ドヨースピア";
		cards[Chara::Patchouli][105] = "サマーフレイム";
		cards[Chara::Patchouli][106] = "コンデンスドバブル";
		cards[Chara::Patchouli][107] = "フラッシュオブスプリング";
		cards[Chara::Patchouli][108] = "オータムブレード";
		cards[Chara::Patchouli][109] = "エメラルドシティ";
		cards[Chara::Patchouli][200] = "火金符「セントエルモピラー」";
		cards[Chara::Patchouli][201] = "土水符「ノエキアンデリュージュ」";
		cards[Chara::Patchouli][202] = "金木符「エレメンタルハーベスター」";
		cards[Chara::Patchouli][203] = "日符「ロイヤルフレア」";
		cards[Chara::Patchouli][204] = "月符「サイレントセレナ」";
		cards[Chara::Patchouli][205] = "火水木金土符「賢者の石」";
		cards[Chara::Patchouli][206] = "水符「ジェリーフィッシュプリンセス」";
		cards[Chara::Patchouli][207] = "月木符「サテライトヒマワリ」";
		cards[Chara::Patchouli][210] = "日木符「フォトシンセシス」";
		cards[Chara::Youmu][100] = "反射下界斬";
		cards[Chara::Youmu][101] = "弦月斬";
		cards[Chara::Youmu][102] = "生死流転斬";
		cards[Chara::Youmu][103] = "憑坐の縛";
		cards[Chara::Youmu][104] = "結跏趺斬";
		cards[Chara::Youmu][105] = "折伏無間";
		cards[Chara::Youmu][106] = "心抄斬";
		cards[Chara::Youmu][107] = "悪し魂";
		cards[Chara::Youmu][109] = "炯眼剣";
		cards[Chara::Youmu][111] = "奇び半身";
		cards[Chara::Youmu][200] = "人符「現世斬」";
		cards[Chara::Youmu][201] = "断命剣「冥想斬」";
		cards[Chara::Youmu][202] = "魂符「幽明の苦輪」";
		cards[Chara::Youmu][203] = "人鬼「未来永劫斬」";
		cards[Chara::Youmu][204] = "断迷剣「迷津慈航斬」";
		cards[Chara::Youmu][205] = "魂魄「幽明求聞持聡明の法」";
		cards[Chara::Youmu][206] = "剣伎「桜花閃々」";
		cards[Chara::Youmu][207] = "断霊剣「成仏得脱斬」";
		cards[Chara::Remilia][100] = "デーモンロードウォーク";
		cards[Chara::Remilia][101] = "サーヴァントフライヤー";
		cards[Chara::Remilia][102] = "デーモンロードクレイドル";
		cards[Chara::Remilia][103] = "デーモンロードアロー";
		cards[Chara::Remilia][104] = "ヴァンパイアクロウ";
		cards[Chara::Remilia][105] = "チェーンギャング";
		cards[Chara::Remilia][106] = "ロケットキックアップ";
		cards[Chara::Remilia][107] = "シーリングフィア";
		cards[Chara::Remilia][109] = "デモンズディナーフォーク";
		cards[Chara::Remilia][200] = "紅符「不夜城レッド」";
		cards[Chara::Remilia][201] = "必殺「ハートブレイク」";
		cards[Chara::Remilia][202] = "夜符「デーモンキングクレイドル」";
		cards[Chara::Remilia][203] = "紅魔「スカーレットデビル」";
		cards[Chara::Remilia][204] = "神槍「スピア・ザ・グングニル」";
		cards[Chara::Remilia][205] = "夜王「ドラキュラクレイドル」";
		cards[Chara::Remilia][206] = "夜符「バッドレディスクランブル」";
		cards[Chara::Remilia][207] = "運命「ミゼラブルフェイト」";
		cards[Chara::Yuyuko][100] = "幽胡蝶";
		cards[Chara::Yuyuko][101] = "未生の光";
		cards[Chara::Yuyuko][102] = "悉皆彷徨";
		cards[Chara::Yuyuko][103] = "胡蝶夢の舞";
		cards[Chara::Yuyuko][104] = "好死の霊";
		cards[Chara::Yuyuko][105] = "鳳蝶紋の槍";
		cards[Chara::Yuyuko][106] = "誘霊の甘蜜";
		cards[Chara::Yuyuko][107] = "逆さ屏風";
		cards[Chara::Yuyuko][108] = "スフィアブルーム";
		cards[Chara::Yuyuko][200] = "死符「ギャストリドリーム」";
		cards[Chara::Yuyuko][201] = "冥符「黄泉平坂行路」";
		cards[Chara::Yuyuko][202] = "霊符「无寿の夢」";
		cards[Chara::Yuyuko][203] = "死蝶「華胥の永眠」";
		cards[Chara::Yuyuko][204] = "再迷「幻想郷の黄泉還り」";
		cards[Chara::Yuyuko][205] = "寿命「无寿国への約束手形」";
		cards[Chara::Yuyuko][206] = "霊蝶「蝶の羽風生に暫く」";
		cards[Chara::Yuyuko][207] = "蝶符「鳳蝶紋の死槍」";
		cards[Chara::Yuyuko][208] = "幽雅「死出の誘蛾灯」";
		cards[Chara::Yukari][100] = "開けて悔しき玉手箱";
		cards[Chara::Yukari][101] = "禅寺に潜む妖蝶";
		cards[Chara::Yukari][102] = "枕石漱流";
		cards[Chara::Yukari][103] = "幻想狂想穴";
		cards[Chara::Yukari][104] = "至る処に青山あり";
		cards[Chara::Yukari][105] = "幻想卍傘";
		cards[Chara::Yukari][106] = "物質と反物質の宇宙";
		cards[Chara::Yukari][107] = "肉体分解機";
		cards[Chara::Yukari][108] = "魅惑のエサ";
		cards[Chara::Yukari][200] = "境符「四重結界」";
		cards[Chara::Yukari][201] = "式神「八雲藍」";
		cards[Chara::Yukari][202] = "境符「二次元と三次元の境界」";
		cards[Chara::Yukari][203] = "結界「魅力的な四重結界」";
		cards[Chara::Yukari][204] = "式神「橙」";
		cards[Chara::Yukari][205] = "結界「客観結界」";
		cards[Chara::Yukari][206] = "幻巣「飛光虫ネスト」";
		cards[Chara::Yukari][207] = "空餌「中毒性のあるエサ」";
		cards[Chara::Yukari][215] = "廃線「ぶらり廃駅下車の旅」";
		cards[Chara::Suika][100] = "妖鬼-密-";
		cards[Chara::Suika][101] = "地霊-密-";
		cards[Chara::Suika][102] = "妖鬼-疎-";
		cards[Chara::Suika][103] = "萃鬼";
		cards[Chara::Suika][104] = "元鬼玉";
		cards[Chara::Suika][105] = "地霊-疎-";
		cards[Chara::Suika][106] = "厭霧";
		cards[Chara::Suika][107] = "疎鬼";
		cards[Chara::Suika][109] = "火鬼";
		cards[Chara::Suika][200] = "萃符「戸隠山投げ」";
		cards[Chara::Suika][201] = "酔神「鬼縛りの術」";
		cards[Chara::Suika][202] = "鬼符「ミッシングパワー」";
		cards[Chara::Suika][203] = "萃鬼「天手力男投げ」";
		cards[Chara::Suika][204] = "酔夢「施餓鬼縛りの術」";
		cards[Chara::Suika][205] = "鬼神「ミッシングパープルパワー」";
		cards[Chara::Suika][206] = "霧符「雲集霧散」";
		cards[Chara::Suika][207] = "鬼火「超高密度燐禍術」";
		cards[Chara::Suika][208] = "鬼符「大江山悉皆殺し」";
		cards[Chara::Reisen][100] = "マインドエクスプロージョン";
		cards[Chara::Reisen][101] = "イリュージョナリィブラスト";
		cards[Chara::Reisen][102] = "フィールドウルトラレッド";
		cards[Chara::Reisen][103] = "ディスビリーフアスペクト";
		cards[Chara::Reisen][104] = "マインドベンディング";
		cards[Chara::Reisen][105] = "アイサイトクリーニング";
		cards[Chara::Reisen][106] = "フィールドウルトラバイオレット";
		cards[Chara::Reisen][107] = "ディスオーダーアイ";
		cards[Chara::Reisen][108] = "マインドドロッピング";
		cards[Chara::Reisen][109] = "リップルヴィジョン";
		cards[Chara::Reisen][110] = "アンダーセンスブレイク";
		cards[Chara::Reisen][200] = "惑視「離円花冠(カローラヴィジョン)」";
		cards[Chara::Reisen][202] = "幻爆「近眼花火(マインドスターマイン)」";
		cards[Chara::Reisen][203] = "幻惑「花冠視線(クラウンヴィジョン)」";
		cards[Chara::Reisen][205] = "「幻朧月睨(ルナティックレッドアイズ)」";
		cards[Chara::Reisen][206] = "弱心「喪心喪意(ディモチヴェイション)」";
		cards[Chara::Reisen][207] = "喪心「喪心創痍(ディスカーダー)」";
		cards[Chara::Reisen][208] = "毒煙幕「瓦斯織物の玉」";
		cards[Chara::Reisen][209] = "生薬「国士無双の薬」";
		cards[Chara::Aya][100] = "疾風扇";
		cards[Chara::Aya][101] = "疾走風靡";
		cards[Chara::Aya][102] = "天狗の立風露";
		cards[Chara::Aya][103] = "暗夜の礫";
		cards[Chara::Aya][104] = "烈風扇";
		cards[Chara::Aya][105] = "疾走優美";
		cards[Chara::Aya][106] = "天狗のダウンバースト";
		cards[Chara::Aya][107] = "鎌風ベーリング";
		cards[Chara::Aya][109] = "天狗ナメシ";
		cards[Chara::Aya][110] = "天狗の太鼓";
		cards[Chara::Aya][200] = "旋符「紅葉扇風」";
		cards[Chara::Aya][201] = "竜巻「天孫降臨の道しるべ」";
		cards[Chara::Aya][202] = "逆風「人間禁制の道」";
		cards[Chara::Aya][203] = "突符「天狗のマクロバースト」";
		cards[Chara::Aya][205] = "風符「天狗道の開風」";
		cards[Chara::Aya][206] = "「幻想風靡」";
		cards[Chara::Aya][211] = "魔獣「鎌鼬ベーリング」";
		cards[Chara::Aya][212] = "突風「猿田彦の先導」";
		cards[Chara::Komachi][100] = "迷わず生きた人霊";
		cards[Chara::Komachi][101] = "浮かばれない地縛霊";
		cards[Chara::Komachi][102] = "脱魂の儀";
		cards[Chara::Komachi][103] = "怠惰に生きた浮遊霊";
		cards[Chara::Komachi][104] = "死神の大鎌";
		cards[Chara::Komachi][105] = "死出の風";
		cards[Chara::Komachi][106] = "無間の道";
		cards[Chara::Komachi][107] = "寂しがり屋の緊縛霊";
		cards[Chara::Komachi][108] = "通りすがりの人霊";
		cards[Chara::Komachi][110] = "お迎え体験版";
		cards[Chara::Komachi][200] = "舟符「河の流れのように」";
		cards[Chara::Komachi][201] = "薄命「余命幾許も無し」";
		cards[Chara::Komachi][202] = "霊符「何処にでもいる浮遊霊」";
		cards[Chara::Komachi][203] = "死歌「八重霧の渡し」";
		cards[Chara::Komachi][204] = "換命「不惜身命、可惜身命」";
		cards[Chara::Komachi][205] = "恨符「未練がましい緊縛霊」";
		cards[Chara::Komachi][206] = "死符「死者選別の鎌」";
		cards[Chara::Komachi][211] = "地獄「無間の狭間」";
		cards[Chara::Iku][100] = "龍魚の一撃";
		cards[Chara::Iku][101] = "羽衣は水の如く";
		cards[Chara::Iku][102] = "龍魚の怒り";
		cards[Chara::Iku][103] = "静電誘導弾";
		cards[Chara::Iku][104] = "龍神の一撃";
		cards[Chara::Iku][105] = "羽衣は風の如く";
		cards[Chara::Iku][106] = "龍神の怒り";
		cards[Chara::Iku][107] = "龍神の稲光り";
		cards[Chara::Iku][111] = "龍の眼";
		cards[Chara::Iku][200] = "電符「雷鼓弾」";
		cards[Chara::Iku][201] = "魚符「龍魚ドリル」";
		cards[Chara::Iku][202] = "雷符「エレキテルの龍宮」";
		cards[Chara::Iku][203] = "光星「光龍の吐息」";
		cards[Chara::Iku][206] = "雷魚「雷雲魚遊泳弾」";
		cards[Chara::Iku][207] = "羽衣「羽衣は空の如く」";
		cards[Chara::Iku][209] = "棘符「雷雲棘魚」";
		cards[Chara::Iku][210] = "龍魚「龍宮の使い遊泳弾」";
		cards[Chara::Tenshi][100] = "坤儀の剣";
		cards[Chara::Tenshi][101] = "天罰の石柱";
		cards[Chara::Tenshi][102] = "非想の威光";
		cards[Chara::Tenshi][103] = "非想の剣";
		cards[Chara::Tenshi][104] = "六震-相-";
		cards[Chara::Tenshi][105] = "守りの要";
		cards[Chara::Tenshi][106] = "天地プレス";
		cards[Chara::Tenshi][107] = "緋想の剣";
		cards[Chara::Tenshi][200] = "地符「不譲土壌の剣」";
		cards[Chara::Tenshi][201] = "非想「非想非非想の剣」";
		cards[Chara::Tenshi][202] = "天符「天道是非の剣」";
		cards[Chara::Tenshi][203] = "地震「先憂後楽の剣」";
		cards[Chara::Tenshi][204] = "気符「天啓気象の剣」";
		cards[Chara::Tenshi][205] = "要石「天地開闢プレス」";
		cards[Chara::Tenshi][206] = "気符「無念無想の境地」";
		cards[Chara::Tenshi][207] = "「全人類の緋想天」";

		return cards;
	}

	map<uint8_t, string> CreateStageMap()
	{
		map<uint8_t, string> stages;

		stages[ 0] = "博麗神社(倒壊)";
		stages[ 1] = "魔法の森";
		stages[ 2] = "玄武の沢";
		stages[ 3] = "妖怪の山";
		stages[ 4] = "玄雲海";
		stages[ 5] = "有頂天";
		stages[ 6] = "緋想天";
		stages[10] = "博麗神社";
		stages[11] = "霧雨魔法店";
		stages[12] = "紅魔館時計台";
		stages[13] = "人形の森";
		stages[14] = "紅魔館大図書館";
		stages[15] = "冥界";
		stages[16] = "紅魔館ロビー";
		stages[17] = "白玉楼の雪庭";
		stages[18] = "迷いの竹林";

		return stages;
	}

	map<uint8_t, string> CreateBgmMap()
	{
		map<uint8_t, string> bgms;

		bgms[ 0] = "地の色は黄色";
		bgms[ 1] = "香る樹葉花";
		bgms[ 2] = "踊る水飛沫";
		bgms[ 3] = "嘲りの遊戯";
		bgms[ 4] = "黒い海に紅く　～ Legendary Fish";
		bgms[ 5] = "有頂天変　～ Wonderful Heaven";
		bgms[ 6] = "幼心地の有頂天";
		bgms[10] = "東方妖恋談";
		bgms[11] = "星の器　～ Casket of Star";
		bgms[12] = "フラワリングナイト";
		bgms[13] = "ブクレシュティの人形師";
		bgms[14] = "広有射怪鳥事　～ Till When？";
		bgms[15] = "ラクトガール　～ 少女密室";
		bgms[16] = "幽雅に咲かせ、墨染の桜　～ Border of Life";
		bgms[17] = "亡き王女の為のセプテット";
		bgms[18] = "夜が降りてくる";
		bgms[19] = "砕月";
		bgms[20] = "狂気の瞳　～ Invisible Full Moon";
		bgms[21] = "風神少女";
		bgms[22] = "彼岸帰航　～ Riverside View";

		return bgms;
	}
}

const map<uint16_t, string> Th105::Versions(::CreateVersionMap());
const map<Mode, string> Th105::Modes(::CreateModeMap());
const map<Chara, string> Th105::Characters(::CreateCharacterMap());
const map<uint16_t, string> Th105::SystemCards(::CreateSystemCardMap());
const map<Chara, map<uint16_t, string>> Th105::Cards(::CreateCardMap());
const map<uint8_t, string> Th105::Stages(::CreateStageMap());
const map<uint8_t, string> Th105::Bgms(::CreateBgmMap());
