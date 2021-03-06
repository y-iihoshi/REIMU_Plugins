#include "StringMaps.h"

using namespace std;
using namespace Th123;

namespace
{
	map<uint16_t, string> CreateVersionMap()
	{
		map<uint16_t, string> versions;

#if 0
		versions[200] = "1.00";
		versions[201] = "1.01";
		versions[202] = "1.02";
		versions[203] = "1.03";
#endif
		versions[210] = "1.10";

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
		characters[Chara::Sanae    ] = "東風谷 早苗";
		characters[Chara::Cirno    ] = "チルノ";
		characters[Chara::Meiling  ] = "紅 美鈴";
		characters[Chara::Utsuho   ] = "霊烏路 空";
		characters[Chara::Suwako   ] = "洩矢 諏訪子";

		return characters;
	}

	map<uint16_t, string> CreateSystemCardMap()
	{
		map<uint16_t, string> cards;

		cards[ 0] = "「霊撃札」";
		cards[ 1] = "「マジックポーション」";
		cards[ 2] = "「ストップウォッチ」";
		cards[ 3] = "「白楼剣」";
		cards[ 4] = "「身代わり人形」";
		cards[ 5] = "「グリモワール」";
		cards[ 6] = "「特注の日傘」";
		cards[ 7] = "「人魂灯」";
		cards[ 8] = "「左扇」";
		cards[ 9] = "「伊吹瓢」";
		cards[10] = "「天狗団扇」";
		cards[11] = "「符蝕薬」";
		cards[12] = "「宵越しの銭」";
		cards[13] = "「龍魚の羽衣」";
		cards[14] = "「緋想の剣」";
		cards[15] = "「病気平癒守」";
		cards[16] = "「冷凍カエル」";
		cards[17] = "「龍星」";
		cards[18] = "「制御棒」";
		cards[19] = "「三粒の天滴」";
		cards[20] = "「ナマズの大地震」";

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
		cards[Chara::Reimu][111] = "雨乞祈り";
		cards[Chara::Reimu][200] = "霊符「夢想妙珠」";
		cards[Chara::Reimu][201] = "神霊「夢想封印」";
		cards[Chara::Reimu][204] = "夢符「封魔陣」";
		cards[Chara::Reimu][206] = "神技「八方鬼縛陣」";
		cards[Chara::Reimu][207] = "結界「拡散結界」";
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
		cards[Chara::Marisa][110] = "マジカル産廃再利用ボム";
		cards[Chara::Marisa][111] = "グリーンスプレッド";
		cards[Chara::Marisa][200] = "恋符「マスタースパーク」";
		cards[Chara::Marisa][202] = "魔砲「ファイナルスパーク」";
		cards[Chara::Marisa][203] = "星符「ドラゴンメテオ」";
		cards[Chara::Marisa][204] = "恋符「ノンディレクショナルレーザー」";
		cards[Chara::Marisa][205] = "魔符「スターダストレヴァリエ」";
		cards[Chara::Marisa][206] = "星符「エスケープベロシティ」";
		cards[Chara::Marisa][207] = "彗星「ブレイジングスター」";
		cards[Chara::Marisa][208] = "星符「メテオニックシャワー」";
		cards[Chara::Marisa][209] = "星符「グラビティビート」";
		cards[Chara::Marisa][211] = "光符「ルミネスストライク」";
		cards[Chara::Marisa][212] = "光符「アースライトレイ」";
		cards[Chara::Marisa][214] = "魔廃「ディープエコロジカルボム」";
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
		cards[Chara::Sakuya][108] = "ダンシングスターソード";
		cards[Chara::Sakuya][109] = "ミスディレクション";
		cards[Chara::Sakuya][110] = "パラレルブレーン";
		cards[Chara::Sakuya][111] = "タイムパラドックス";
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
		cards[Chara::Sakuya][210] = "光速「Ｃ．リコシェ」";
		cards[Chara::Sakuya][211] = "時符「イマジナリバーチカルタイム」";
		cards[Chara::Sakuya][212] = "時計「ルナダイアル」";
		cards[Chara::Alice][100] = "人形操創";
		cards[Chara::Alice][101] = "人形無操";
		cards[Chara::Alice][102] = "人形置操";
		cards[Chara::Alice][103] = "人形振起";
		cards[Chara::Alice][104] = "人形帰巣";
		cards[Chara::Alice][105] = "人形火葬";
		cards[Chara::Alice][106] = "人形千槍";
		cards[Chara::Alice][107] = "人形ＳＰ";
		cards[Chara::Alice][108] = "人形伏兵";
		cards[Chara::Alice][109] = "大江戸爆薬からくり人形";
		cards[Chara::Alice][110] = "人形弓兵";
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
		cards[Chara::Alice][210] = "槍符「キューティ大千槍」";
		cards[Chara::Alice][211] = "人形「レミングスパレード」";
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
		cards[Chara::Patchouli][110] = "ワイプモイスチャー";
		cards[Chara::Patchouli][111] = "スティッキーバブル";
		cards[Chara::Patchouli][112] = "スタティックグリーン";
		cards[Chara::Patchouli][113] = "フォールスラッシャー";
		cards[Chara::Patchouli][114] = "ダイアモンドハードネス";
		cards[Chara::Patchouli][200] = "火金符「セントエルモピラー」";
		cards[Chara::Patchouli][201] = "土水符「ノエキアンデリュージュ」";
		cards[Chara::Patchouli][202] = "金木符「エレメンタルハーベスター」";
		cards[Chara::Patchouli][203] = "日符「ロイヤルフレア」";
		cards[Chara::Patchouli][204] = "月符「サイレントセレナ」";
		cards[Chara::Patchouli][205] = "火水木金土符「賢者の石」";
		cards[Chara::Patchouli][206] = "水符「ジェリーフィッシュプリンセス」";
		cards[Chara::Patchouli][207] = "月木符「サテライトヒマワリ」";
		cards[Chara::Patchouli][210] = "日木符「フォトシンセシス」";
		cards[Chara::Patchouli][211] = "火水符「フロギスティックピラー」";
		cards[Chara::Patchouli][212] = "土金符「エメラルドメガロポリス」";
		cards[Chara::Patchouli][213] = "日月符「ロイヤルダイアモンドリング」";
		cards[Chara::Youmu][100] = "反射下界斬";
		cards[Chara::Youmu][101] = "弦月斬";
		cards[Chara::Youmu][102] = "生死流転斬";
		cards[Chara::Youmu][103] = "憑坐の縛";
		cards[Chara::Youmu][104] = "結跏趺斬";
		cards[Chara::Youmu][105] = "折伏無間";
		cards[Chara::Youmu][106] = "心抄斬";
		cards[Chara::Youmu][107] = "悪し魂";
		cards[Chara::Youmu][108] = "燐気斬";
		cards[Chara::Youmu][109] = "炯眼剣";
		cards[Chara::Youmu][110] = "頭上花剪斬";
		cards[Chara::Youmu][111] = "奇び半身";
		cards[Chara::Youmu][200] = "人符「現世斬」";
		cards[Chara::Youmu][201] = "断命剣「冥想斬」";
		cards[Chara::Youmu][202] = "魂符「幽明の苦輪」";
		cards[Chara::Youmu][203] = "人鬼「未来永劫斬」";
		cards[Chara::Youmu][204] = "断迷剣「迷津慈航斬」";
		cards[Chara::Youmu][205] = "魂魄「幽明求聞持聡明の法」";
		cards[Chara::Youmu][206] = "剣伎「桜花閃々」";
		cards[Chara::Youmu][207] = "断霊剣「成仏得脱斬」";
		cards[Chara::Youmu][208] = "空観剣「六根清浄斬」";
		cards[Chara::Youmu][212] = "転生剣「円心流転斬」";
		cards[Chara::Remilia][100] = "デーモンロードウォーク";
		cards[Chara::Remilia][101] = "サーヴァントフライヤー";
		cards[Chara::Remilia][102] = "デーモンロードクレイドル";
		cards[Chara::Remilia][103] = "デーモンロードアロー";
		cards[Chara::Remilia][104] = "ヴァンパイアクロウ";
		cards[Chara::Remilia][105] = "チェーンギャング";
		cards[Chara::Remilia][106] = "ロケットキックアップ";
		cards[Chara::Remilia][107] = "シーリングフィア";
		cards[Chara::Remilia][108] = "トリックスターデビル";
		cards[Chara::Remilia][109] = "デモンズディナーフォーク";
		cards[Chara::Remilia][110] = "バンパイアキス";
		cards[Chara::Remilia][111] = "スティグマナイザー";
		cards[Chara::Remilia][200] = "紅符「不夜城レッド」";
		cards[Chara::Remilia][201] = "必殺「ハートブレイク」";
		cards[Chara::Remilia][202] = "夜符「デーモンキングクレイドル」";
		cards[Chara::Remilia][203] = "紅魔「スカーレットデビル」";
		cards[Chara::Remilia][204] = "神槍「スピア・ザ・グングニル」";
		cards[Chara::Remilia][205] = "夜王「ドラキュラクレイドル」";
		cards[Chara::Remilia][206] = "夜符「バッドレディスクランブル」";
		cards[Chara::Remilia][207] = "運命「ミゼラブルフェイト」";
		cards[Chara::Remilia][208] = "「ミレニアムの吸血鬼」";
		cards[Chara::Remilia][209] = "悪魔「レミリアストレッチ」";
		cards[Chara::Yuyuko][100] = "幽胡蝶";
		cards[Chara::Yuyuko][101] = "未生の光";
		cards[Chara::Yuyuko][102] = "悉皆彷徨";
		cards[Chara::Yuyuko][103] = "胡蝶夢の舞";
		cards[Chara::Yuyuko][104] = "好死の霊";
		cards[Chara::Yuyuko][105] = "鳳蝶紋の槍";
		cards[Chara::Yuyuko][106] = "誘霊の甘蜜";
		cards[Chara::Yuyuko][107] = "逆さ屏風";
		cards[Chara::Yuyuko][108] = "スフィアブルーム";
		cards[Chara::Yuyuko][109] = "死還の大地";
		cards[Chara::Yuyuko][110] = "故人のお届け物";
		cards[Chara::Yuyuko][111] = "センスオブエレガンス";
		cards[Chara::Yuyuko][200] = "死符「ギャストリドリーム」";
		cards[Chara::Yuyuko][201] = "冥符「黄泉平坂行路」";
		cards[Chara::Yuyuko][202] = "霊符「无寿の夢」";
		cards[Chara::Yuyuko][203] = "死蝶「華胥の永眠」";
		cards[Chara::Yuyuko][204] = "再迷「幻想郷の黄泉還り」";
		cards[Chara::Yuyuko][205] = "寿命「无寿国への約束手形」";
		cards[Chara::Yuyuko][206] = "霊蝶「蝶の羽風生に暫く」";
		cards[Chara::Yuyuko][207] = "蝶符「鳳蝶紋の死槍」";
		cards[Chara::Yuyuko][208] = "幽雅「死出の誘蛾灯」";
		cards[Chara::Yuyuko][209] = "桜符「センスオブチェリーブロッサム」";
		cards[Chara::Yuyuko][219] = "「反魂蝶」";
		cards[Chara::Yukari][100] = "開けて悔しき玉手箱";
		cards[Chara::Yukari][101] = "禅寺に潜む妖蝶";
		cards[Chara::Yukari][102] = "枕石漱流";
		cards[Chara::Yukari][103] = "幻想狂想穴";
		cards[Chara::Yukari][104] = "至る処に青山あり";
		cards[Chara::Yukari][105] = "幻想卍傘";
		cards[Chara::Yukari][106] = "物質と反物質の宇宙";
		cards[Chara::Yukari][107] = "肉体分解機";
		cards[Chara::Yukari][108] = "魅惑のエサ";
		cards[Chara::Yukari][109] = "知能と脚の境界";
		cards[Chara::Yukari][110] = "変容を見る眼";
		cards[Chara::Yukari][111] = "キマイラの翼";
		cards[Chara::Yukari][200] = "境符「四重結界」";
		cards[Chara::Yukari][201] = "式神「八雲藍」";
		cards[Chara::Yukari][202] = "境符「二次元と三次元の境界」";
		cards[Chara::Yukari][203] = "結界「魅力的な四重結界」";
		cards[Chara::Yukari][204] = "式神「橙」";
		cards[Chara::Yukari][205] = "結界「客観結界」";
		cards[Chara::Yukari][206] = "幻巣「飛光虫ネスト」";
		cards[Chara::Yukari][207] = "空餌「中毒性のあるエサ」";
		cards[Chara::Yukari][208] = "魔眼「ラプラスの魔」";
		cards[Chara::Yukari][215] = "廃線「ぶらり廃駅下車の旅」";
		cards[Chara::Suika][100] = "妖鬼-密-";
		cards[Chara::Suika][101] = "地霊-密-";
		cards[Chara::Suika][102] = "妖鬼-疎-";
		cards[Chara::Suika][103] = "萃鬼";
		cards[Chara::Suika][104] = "元鬼玉";
		cards[Chara::Suika][105] = "地霊-疎-";
		cards[Chara::Suika][106] = "厭霧";
		cards[Chara::Suika][107] = "疎鬼";
		cards[Chara::Suika][108] = "踏鞴";
		cards[Chara::Suika][109] = "火鬼";
		cards[Chara::Suika][110] = "鬼神燐火術";
		cards[Chara::Suika][111] = "攫鬼";
		cards[Chara::Suika][200] = "萃符「戸隠山投げ」";
		cards[Chara::Suika][201] = "酔神「鬼縛りの術」";
		cards[Chara::Suika][202] = "鬼符「ミッシングパワー」";
		cards[Chara::Suika][203] = "萃鬼「天手力男投げ」";
		cards[Chara::Suika][204] = "酔夢「施餓鬼縛りの術」";
		cards[Chara::Suika][205] = "鬼神「ミッシングパープルパワー」";
		cards[Chara::Suika][206] = "霧符「雲集霧散」";
		cards[Chara::Suika][207] = "鬼火「超高密度燐禍術」";
		cards[Chara::Suika][208] = "鬼符「大江山悉皆殺し」";
		cards[Chara::Suika][212] = "四天王奥義「三歩壊廃」";
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
		cards[Chara::Reisen][111] = "アキュラースペクトル";
		cards[Chara::Reisen][200] = "惑視「離円花冠(カローラヴィジョン)」";
		cards[Chara::Reisen][202] = "幻爆「近眼花火(マインドスターマイン)」";
		cards[Chara::Reisen][203] = "幻惑「花冠視線(クラウンヴィジョン)」";
		cards[Chara::Reisen][204] = "赤眼「望見円月(ルナティックブラスト)」";
		cards[Chara::Reisen][205] = "「幻朧月睨(ルナティックレッドアイズ)」";
		cards[Chara::Reisen][206] = "弱心「喪心喪意(ディモチヴェイション)」";
		cards[Chara::Reisen][207] = "喪心「喪心創痍(ディスカーダー)」";
		cards[Chara::Reisen][208] = "毒煙幕「瓦斯織物の玉」";
		cards[Chara::Reisen][209] = "生薬「国士無双の薬」";
		cards[Chara::Reisen][210] = "短視「超短脳波(エックスウェイブ)」";
		cards[Chara::Reisen][211] = "長視「赤月下(インフレアドムーン)」";
		cards[Chara::Aya][100] = "疾風扇";
		cards[Chara::Aya][101] = "疾走風靡";
		cards[Chara::Aya][102] = "天狗の立風露";
		cards[Chara::Aya][103] = "暗夜の礫";
		cards[Chara::Aya][104] = "烈風扇";
		cards[Chara::Aya][105] = "疾走優美";
		cards[Chara::Aya][106] = "天狗のダウンバースト";
		cards[Chara::Aya][107] = "鎌風ベーリング";
		cards[Chara::Aya][108] = "楓扇風";
		cards[Chara::Aya][109] = "天狗ナメシ";
		cards[Chara::Aya][110] = "天狗の太鼓";
		cards[Chara::Aya][111] = "天狗礫";
		cards[Chara::Aya][200] = "旋符「紅葉扇風」";
		cards[Chara::Aya][201] = "竜巻「天孫降臨の道しるべ」";
		cards[Chara::Aya][202] = "逆風「人間禁制の道」";
		cards[Chara::Aya][203] = "突符「天狗のマクロバースト」";
		cards[Chara::Aya][205] = "風符「天狗道の開風」";
		cards[Chara::Aya][206] = "「幻想風靡」";
		cards[Chara::Aya][207] = "風符「天狗報即日限」";
		cards[Chara::Aya][208] = "鴉符「暗夜のデイメア」";
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
		cards[Chara::Komachi][109] = "三途の舟";
		cards[Chara::Komachi][110] = "お迎え体験版";
		cards[Chara::Komachi][111] = "離魂の鎌";
		cards[Chara::Komachi][200] = "舟符「河の流れのように」";
		cards[Chara::Komachi][201] = "薄命「余命幾許も無し」";
		cards[Chara::Komachi][202] = "霊符「何処にでもいる浮遊霊」";
		cards[Chara::Komachi][203] = "死歌「八重霧の渡し」";
		cards[Chara::Komachi][204] = "換命「不惜身命、可惜身命」";
		cards[Chara::Komachi][205] = "恨符「未練がましい緊縛霊」";
		cards[Chara::Komachi][206] = "死符「死者選別の鎌」";
		cards[Chara::Komachi][207] = "魂符「生魂流離の鎌」";
		cards[Chara::Komachi][211] = "地獄「無間の狭間」";
		cards[Chara::Iku][100] = "龍魚の一撃";
		cards[Chara::Iku][101] = "羽衣は水の如く";
		cards[Chara::Iku][102] = "龍魚の怒り";
		cards[Chara::Iku][103] = "静電誘導弾";
		cards[Chara::Iku][104] = "龍神の一撃";
		cards[Chara::Iku][105] = "羽衣は風の如く";
		cards[Chara::Iku][106] = "龍神の怒り";
		cards[Chara::Iku][107] = "龍神の稲光り";
		cards[Chara::Iku][108] = "水得の龍魚";
		cards[Chara::Iku][109] = "天女の一撃";
		cards[Chara::Iku][110] = "龍神の髭";
		cards[Chara::Iku][111] = "龍の眼";
		cards[Chara::Iku][200] = "電符「雷鼓弾」";
		cards[Chara::Iku][201] = "魚符「龍魚ドリル」";
		cards[Chara::Iku][202] = "雷符「エレキテルの龍宮」";
		cards[Chara::Iku][203] = "光星「光龍の吐息」";
		cards[Chara::Iku][206] = "雷魚「雷雲魚遊泳弾」";
		cards[Chara::Iku][207] = "羽衣「羽衣は空の如く」";
		cards[Chara::Iku][208] = "羽衣「羽衣は時の如く」";
		cards[Chara::Iku][209] = "棘符「雷雲棘魚」";
		cards[Chara::Iku][210] = "龍魚「龍宮の使い遊泳弾」";
		cards[Chara::Iku][211] = "珠符「五爪龍の珠」";
		cards[Chara::Tenshi][100] = "坤儀の剣";
		cards[Chara::Tenshi][101] = "天罰の石柱";
		cards[Chara::Tenshi][102] = "非想の威光";
		cards[Chara::Tenshi][103] = "非想の剣";
		cards[Chara::Tenshi][104] = "六震-相-";
		cards[Chara::Tenshi][105] = "守りの要";
		cards[Chara::Tenshi][106] = "天地プレス";
		cards[Chara::Tenshi][107] = "緋想の剣";
		cards[Chara::Tenshi][108] = "因果の剣";
		cards[Chara::Tenshi][109] = "地精の起床";
		cards[Chara::Tenshi][110] = "緋想の剣気";
		cards[Chara::Tenshi][111] = "昇天突";
		cards[Chara::Tenshi][200] = "地符「不譲土壌の剣」";
		cards[Chara::Tenshi][201] = "非想「非想非非想の剣」";
		cards[Chara::Tenshi][202] = "天符「天道是非の剣」";
		cards[Chara::Tenshi][203] = "地震「先憂後楽の剣」";
		cards[Chara::Tenshi][204] = "気符「天啓気象の剣」";
		cards[Chara::Tenshi][205] = "要石「天地開闢プレス」";
		cards[Chara::Tenshi][206] = "気符「無念無想の境地」";
		cards[Chara::Tenshi][207] = "「全人類の緋想天」";
		cards[Chara::Tenshi][208] = "剣技「気炎万丈の剣」";
		cards[Chara::Tenshi][209] = "天気「緋想天促」";
        cards[Chara::Sanae][100] = "風起こし";
        cards[Chara::Sanae][101] = "おみくじ爆弾";
        cards[Chara::Sanae][102] = "乾神招来　突";
        cards[Chara::Sanae][103] = "坤神招来　盾";
        cards[Chara::Sanae][104] = "波起こし";
        cards[Chara::Sanae][105] = "スカイサーペント";
        cards[Chara::Sanae][106] = "乾神招来　風";
        cards[Chara::Sanae][107] = "坤神招来　鉄輪";
        cards[Chara::Sanae][108] = "星落とし";
        cards[Chara::Sanae][109] = "コバルトスプレッド";
        cards[Chara::Sanae][110] = "乾神招来　御柱";
        cards[Chara::Sanae][111] = "坤神招来　罠";
        cards[Chara::Sanae][200] = "祈願「商売繁盛守り」";
        cards[Chara::Sanae][201] = "秘術「グレイソーマタージ」";
        cards[Chara::Sanae][202] = "秘術「忘却の祭儀」";
        cards[Chara::Sanae][203] = "神籤「乱れおみくじ連続引き」";
        cards[Chara::Sanae][204] = "開海「海が割れる日」";
        cards[Chara::Sanae][205] = "開海「モーゼの奇跡」";
        cards[Chara::Sanae][206] = "奇跡「白昼の客星」";
        cards[Chara::Sanae][207] = "奇跡「客星の明るすぎる夜」";
        cards[Chara::Sanae][210] = "秘法「九字刺し」";
        cards[Chara::Cirno][100] = "アイシクルシュート";
        cards[Chara::Cirno][101] = "真夏のスノーマン";
        cards[Chara::Cirno][102] = "リトルアイスバーグ";
        cards[Chara::Cirno][103] = "フリーズタッチミー";
        cards[Chara::Cirno][104] = "フロストピラーズ";
        cards[Chara::Cirno][105] = "アイスチャージ";
        cards[Chara::Cirno][106] = "アイシクルボム";
        cards[Chara::Cirno][107] = "アイシクルライズ";
        cards[Chara::Cirno][108] = "冷凍光線";
        cards[Chara::Cirno][109] = "アイスキック";
        cards[Chara::Cirno][110] = "フローズン冷凍法";
        cards[Chara::Cirno][111] = "アイシクルソード";
        cards[Chara::Cirno][200] = "氷符「アイシクルマシンガン」";
        cards[Chara::Cirno][201] = "霜符「フロストコラムス」";
        cards[Chara::Cirno][202] = "氷塊「コールドスプリンクラー」";
        cards[Chara::Cirno][203] = "冷体「スーパーアイスキック」";
        cards[Chara::Cirno][204] = "凍符「パーフェクトフリーズ」";
        cards[Chara::Cirno][205] = "氷符「フェアリースピン」";
        cards[Chara::Cirno][206] = "吹氷「アイストルネード」";
        cards[Chara::Cirno][207] = "氷符「ソードフリーザー」";
        cards[Chara::Cirno][208] = "氷塊「グレートクラッシャー」";
        cards[Chara::Cirno][210] = "凍符「フリーズアトモスフェア」";
        cards[Chara::Cirno][213] = "冷符「瞬間冷凍ビーム」";
        cards[Chara::Meiling][100] = "螺光歩";
        cards[Chara::Meiling][101] = "紅砲";
        cards[Chara::Meiling][102] = "黄震脚";
        cards[Chara::Meiling][103] = "芳波";
        cards[Chara::Meiling][104] = "烈虹拳";
        cards[Chara::Meiling][105] = "紅寸剄";
        cards[Chara::Meiling][106] = "地龍波";
        cards[Chara::Meiling][107] = "水形太極拳";
        cards[Chara::Meiling][108] = "降華蹴";
        cards[Chara::Meiling][109] = "虎剄";
        cards[Chara::Meiling][110] = "天龍脚";
        cards[Chara::Meiling][111] = "彩雨";
        cards[Chara::Meiling][200] = "彩符「彩光風鈴」";
        cards[Chara::Meiling][201] = "極彩「彩光乱舞」";
        cards[Chara::Meiling][202] = "気符「星脈弾」";
        cards[Chara::Meiling][203] = "星気「星脈地転弾」";
        cards[Chara::Meiling][204] = "撃符「大鵬拳」";
        cards[Chara::Meiling][205] = "熾撃「大鵬墜撃拳」";
        cards[Chara::Meiling][206] = "虹符「烈虹真拳」";
        cards[Chara::Meiling][207] = "気符「地龍天龍脚」";
        cards[Chara::Meiling][208] = "彩華「虹色太極拳」";
        cards[Chara::Meiling][209] = "華符「彩光蓮華掌」";
        cards[Chara::Meiling][211] = "気符「猛虎内剄」";
        cards[Chara::Utsuho][100] = "フレアアップ";
        cards[Chara::Utsuho][101] = "グラウンドメルト";
        cards[Chara::Utsuho][102] = "ブレイクサン";
        cards[Chara::Utsuho][103] = "シューティングスター";
        cards[Chara::Utsuho][104] = "ロケットダイブ";
        cards[Chara::Utsuho][105] = "ヘルゲイザー";
        cards[Chara::Utsuho][106] = "シューティングサン";
        cards[Chara::Utsuho][107] = "レトロ原子核モデル";
        cards[Chara::Utsuho][108] = "メルティング浴びせ蹴り";
        cards[Chara::Utsuho][109] = "レイディアントブレード";
        cards[Chara::Utsuho][110] = "地獄波動砲";
        cards[Chara::Utsuho][111] = "核熱の怨霊";
        cards[Chara::Utsuho][200] = "爆符「メガフレア」";
        cards[Chara::Utsuho][201] = "爆符「ギガフレア」";
        cards[Chara::Utsuho][203] = "焔星「フィクストスター」";
        cards[Chara::Utsuho][204] = "焔星「十凶星」";
        cards[Chara::Utsuho][205] = "核符「クリーピングサン」";
        cards[Chara::Utsuho][206] = "「地獄の人工太陽」";
        cards[Chara::Utsuho][207] = "地熱「核ブレイズゲイザー」";
        cards[Chara::Utsuho][208] = "光熱「ハイテンションブレード」";
        cards[Chara::Utsuho][209] = "鴉符「八咫烏ダイブ」";
        cards[Chara::Utsuho][210] = "核熱「核反応制御不能ダイブ」";
        cards[Chara::Utsuho][211] = "制御「セルフトカマク」";
        cards[Chara::Utsuho][212] = "「サブタレイニアンサン」";
        cards[Chara::Utsuho][213] = "遮光「核熱バイザー」";
        cards[Chara::Utsuho][214] = "「アビスノヴァ」";
        cards[Chara::Suwako][100] = "古の間欠泉";
        cards[Chara::Suwako][101] = "大蝦蟇神";
        cards[Chara::Suwako][102] = "大地の湖";
        cards[Chara::Suwako][103] = "土着神の祟り";
        cards[Chara::Suwako][104] = "水蛙神";
        cards[Chara::Suwako][105] = "古の鉄輪";
        cards[Chara::Suwako][106] = "古代翡翠";
        cards[Chara::Suwako][107] = "祟られた大地";
        cards[Chara::Suwako][108] = "雨を呼ぶ雨蛙";
        cards[Chara::Suwako][109] = "手長足長さん";
        cards[Chara::Suwako][110] = "蛙石神";
        cards[Chara::Suwako][111] = "ミシャグジさまの祟り";
        cards[Chara::Suwako][200] = "土着神「洩矢神」";
        cards[Chara::Suwako][201] = "源符「諏訪清水」";
        cards[Chara::Suwako][202] = "開宴「二拝二拍一拝」";
        cards[Chara::Suwako][203] = "土着神「ケロちゃん風雨に負けず」";
        cards[Chara::Suwako][204] = "神具「洩矢の鉄の輪」";
        cards[Chara::Suwako][205] = "源符「厭い川の翡翠」";
        cards[Chara::Suwako][206] = "蛙狩「蛙は口ゆえ蛇に呑まるる」";
        cards[Chara::Suwako][207] = "土着神「手長足長さま」";
        cards[Chara::Suwako][208] = "祟り神「赤口（ミシャグチ）さま」";
        cards[Chara::Suwako][209] = "土着神「宝永四年の赤蛙」";
        cards[Chara::Suwako][212] = "蛙休「オールウェイズ冬眠できます」";

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
		stages[30] = "霧の湖の辺";
		stages[31] = "守矢神社";
		stages[32] = "間欠泉地下センター入口";
		stages[33] = "間欠泉地下センター通路";
		stages[34] = "核融合炉心部";
		stages[35] = "真っ暗なステージ";
		stages[36] = "時計台(美鈴ストーリー)";
		stages[37] = "時計台２(美鈴ストーリー)";
		stages[38] = "美鈴ストーリーラスト";

		return stages;
	}

	map<uint8_t, string> CreateBgmMap()
	{
		map<uint8_t, string> bgms;

		bgms[ 0] = "地の色は黄色";
		bgms[ 1] = "香る樹葉花";
		bgms[ 2] = "踊る水飛沫";
		bgms[ 3] = "嘲りの遊戯";
		bgms[ 4] = "黒い海に紅く　〜 Legendary Fish";
		bgms[ 5] = "有頂天変　〜 Wonderful Heaven";
		bgms[ 6] = "幼心地の有頂天";
		bgms[10] = "東方妖恋談";
		bgms[11] = "星の器　〜 Casket of Star";
		bgms[12] = "フラワリングナイト";
		bgms[13] = "ブクレシュティの人形師";
		bgms[14] = "広有射怪鳥事　〜 Till When？";
		bgms[15] = "ラクトガール　〜 少女密室";
		bgms[16] = "幽雅に咲かせ、墨染の桜　〜 Border of Life";
		bgms[17] = "亡き王女の為のセプテット";
		bgms[18] = "夜が降りてくる";
		bgms[19] = "砕月";
		bgms[20] = "狂気の瞳　〜 Invisible Full Moon";
		bgms[21] = "風神少女";
		bgms[22] = "彼岸帰航　〜 Riverside View";
		bgms[30] = "信仰は儚き人間の為に";
		bgms[31] = "おてんば恋娘";
		bgms[32] = "上海紅茶館　〜 Chinese Tea";
		bgms[33] = "霊知の太陽信仰　〜 Nuclear Fusion";
		bgms[34] = "明日ハレの日、ケの昨日";
		bgms[35] = "アンノウンＸ　〜 Unfound Adventure";
		bgms[36] = "空に浮かぶ物体Ｘ";
		bgms[40] = "二色蓮花蝶　〜 Ancients";
		bgms[41] = "恋色マジック";
		bgms[42] = "the Grimoire of Alice";
		bgms[43] = "ヴワル魔法図書館";

		return bgms;
	}
}

const map<uint16_t, string> Th123::Versions(::CreateVersionMap());
const map<Mode, string> Th123::Modes(::CreateModeMap());
const map<Chara, string> Th123::Characters(::CreateCharacterMap());
const map<uint16_t, string> Th123::SystemCards(::CreateSystemCardMap());
const map<Chara, map<uint16_t, string>> Th123::Cards(::CreateCardMap());
const map<uint8_t, string> Th123::Stages(::CreateStageMap());
const map<uint8_t, string> Th123::Bgms(::CreateBgmMap());
