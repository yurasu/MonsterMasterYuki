#include "StagePrinter.h"
#include "Stage.h"
#include "DblBuffer.h"
#include <locale.h>

StagePrinter::StagePrinter(Stage * stage)
{
	this->s = stage;
}

void StagePrinter::print_board()
{
	buff.setCursorPos(0, 2);
	buff.setColor(COL_WHITE, COL_BLACK);
	for (int y = 1; y <= BOARD_HT; ++y) {
		print_line(y, false);
		print_line(y, false);
		print_line(y, true);
		print_line(y, false);
		print_line(y, false);
	}
	buff.write("\n");
	show_explanatory_text();
	buff.setColor(COL_WHITE, COL_BLACK);

}


void StagePrinter::print_line(int y, bool printval)
{
	for (int x = 1; x <= BOARD_WD; ++x) {
		int i = s->board[x][y];
		buff.setColor(COL_WHITE, COL_LIGHT_GRAY);
		vector<CurPos> v;
		s->pmonster[s->move_monster]->moveable_range(v, s->board);
		movable_draw(v, x, y);
		if (x == s->player_curpos.first && y == s->player_curpos.second) {
			buff.setColor(COL_WHITE, COL_BLACK);
		}
		line_write(printval);
	}
	buff.setColor(COL_WHITE, COL_BLACK);
	buff.write("\n");
}

void StagePrinter::line_write(bool printval, bool monsterstr, int attr) {
	string str(CELL_WIDTH, ' ');
	if (printval) {
		str = '.';
		if (monsterstr) {
			str = str_attribute(attr);
		}
		str += string((CELL_WIDTH - str.size()) / 2, ' ');      //  末尾に空白パディング
		str = string(CELL_WIDTH - str.size(), ' ') + str;       //  先頭に空白パディング
	}
	buff.write(str);
}

void StagePrinter::movable_draw(vector<CurPos> v, int x, int y)
{
	for (auto itr = v.begin(); itr != v.end(); itr++) {
		int w = itr->first;
		int h = itr->second;
		if (w == x && h == y) {
			buff.setColor(COL_BLACK, COL_WHITE);
		}

	}

}

char * StagePrinter::str_attribute(int v)
{
	switch (v) {
	case TRAP:
		return ".";
	case GOO:
		//case ENEMY_GOO:
		return "グ";
	case CHOKI:
		//case ENEMY_CHOKI:
		return "チ";
	case PER:
		//case ENEMY_PER:
		return "パ";
	case TATUYA:
		return "兄";
	default:
		return "E";
	}
}

void StagePrinter::setMonsterColor(int v)
{
	int fg = COL_WHITE;
	int bg = COL_BLACK;
	switch (v) {
	case TRAP:
		bg = COL_LIGHT_GRAY;
		break;
	case GOO:
		bg = COL_DARK_RED;
		break;
	case PER:
		bg = COL_DARK_CYAN;
		break;
	case CHOKI:
		bg = COL_DARK_GREEN;
		break;
	case TATUYA:
		bg = COL_DARK_VIOLET;
		break;
	default:
		bg = COL_DARK_YELLOW;
		break;
	}
	buff.setColor(fg, bg);
}

void StagePrinter::draw_board_monsters(int x, int y, bool animation)
{
	EnemyMonster **e_array = s->penemy;
	AllyMonster **m_array = s->pmonster;
	CurPos mapping_pos;
	for (int i = 0; i < s->emonsters_length; i++) {
		if (e_array[i]->is_dead()) {
			continue;
		}
		mapping_coordinate(e_array[i]->pos, mapping_pos);
		if (animation && x == e_array[i]->pos.first && y == e_array[i]->pos.second) {
			continue;
		}
		int w = mapping_pos.first;
		int v = mapping_pos.second;
		DrawMonster(w, v, e_array[i]->getAttr(), s->player_curpos);

	}
	for (int i = 0; i < s->monsters_length; i++) {
		if (m_array[i]->is_dead()) {
			continue;
		}
		mapping_coordinate(m_array[i]->pos, mapping_pos);
		if (animation && x == m_array[i]->pos.first && y == m_array[i]->pos.second) {
			continue;
		}
		int w = mapping_pos.first;
		int v = mapping_pos.second;
		DrawMonster(w, v, m_array[i]->getAttr(), s->player_curpos);
	}
}

void StagePrinter::clear()
{
	buff.clearBuff();
}

void StagePrinter::helpText()
{
	if (!s->help) {
		clear();
		return;
	}
	CurPos size;
	string str;
	buff.getBuffSize(size);
	TextBox t(80, 28, &buff);
	print_board();
	int x = 23;
	draw_board_monsters();
	t.animation(20, size.second / 4 -8);
	buff.setColor(COL_BLACK, COL_WHITE);
	int y = 3;
	if (s->stage_number == 1) {
		buff.setCursorPos(x, y);
		str = "ステージ1  ";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "YUKI君！YUKI君！聞こえる？よかったぁ無事なのね？";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "私？私も今は平気よ！";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "なんで話ができるかって？そんなの愛の力に決まってるじゃない！";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "そんなことよりも敵が来てるわよ！";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "モンスターの扱い方はYUKIの方が知ってるわよね？ ";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "覚えてなかったら左の画面を見るといいわ。  ";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "ヘタレなYUKIでもわかるように体力やステージの場所も見えるようにしたわ！";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "ちなみにこのステージだけど・・・		";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "ヘタレなYUKIでも何も考えずに進めば勝てるわ！頑張って！";
		buff.write(str);
		buff.swap();
	}
	else if (s->stage_number == 2) {
		buff.setCursorPos(x, y);
		str = "ステージ2 ";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "何とか勝てたみたいねYUKIにしては上出来じゃない！。";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "でもまだステージ1よ。これからが本番なんだからね！。";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "このステージ2は爆弾が仕掛けられているの踏んだらどっかーん！って仕掛けらしいわ。 ";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "ん～このステージはYUKI君にぴったりね！";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "だってあなた、私といる時いつもその場であたふたして何もしないじゃない。";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "覚えてなかったら左の画面を見るといいわ。";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "その調子でいけば勝てるんじゃない?";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "爆弾踏んで死なないようにね？";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "次のステージに進めることを祈ってるわ。";
		buff.write(str);
		buff.swap();
	}
	else if (s->stage_number == 3) {
		buff.setCursorPos(x, y);
		str = "ステージ3 ";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "YUKI君、爆弾避けられたのはいいんだけど・・・。";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "モンスターに踏ませるのはよくないと思うわ！かわいそうじゃない！。";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "でも無事でよかったわ。今は無事ではなさそうですけどぉ～。";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "もう敵に囲まれちゃってるじゃない！";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "YUKI君まだ3体しかモンスター出せないんだから今ある力でなんとしなさい！";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "そうねぇ・・・。モンスターを突撃させ続けるってのはどうかしら？		";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "そうすれば自然といなくなるわよ！きっと！";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "あなたの体力と敵の軍団どっちが持つかしらね？";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "私はあなたの体力が持つことを信じているわ。";
		buff.write(str);
		buff.swap();
	}
	else if (s->stage_number == 4) {
		buff.setCursorPos(x, y);
		str = "ステージ4 ";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "とうとうここまで来たわね！";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "もうボロボロじゃない。大丈夫？";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "あなたのモンスターも辛そうね・・・。";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "ん？ずいぶんと魔王の評価が高くないかって？そっそんなわけないじゃない！";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "そんなことよりも魔王よ。あのお方は強敵よ。	";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "あなたの今の力じゃ3回攻撃を仕掛けないと倒せないかも。";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "モンスターの側近はいつも道理だから大丈夫だとは思うけど・・・。";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "油断は禁物よ！でもどんなにつらくてもYUKI君は自分を信じて！";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "あきらめなければきっと勝てるわ！";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "もし怖くなったり自身がなくなった時は・・・・・。";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "魔王なんか無視して私のところへ来てもいいわ！！！。";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "私は魔王の後ろにある椅子に座って待ってるわ。";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "頑張ってYUKI君。";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "私の最も愛しい人。";
		buff.write(str);
		buff.swap();
	}
}


void StagePrinter::DrawMonster(int x, int y, int attr, CurPos pos)
{
	setMonsterColor(attr);
	CurPos p_mapping_pos;
	mapping_coordinate(pos, p_mapping_pos);
	if (x == p_mapping_pos.first && y == p_mapping_pos.second) {
		buff.setColor(COL_WHITE, COL_BLACK);
	}

	for (int i = 0; i < BOARD_HT; i++) {
		bool printval = false;
		buff.setCursorPos(x, y + i);
		if (i == 2) {
			printval = true;
		}
		line_write(printval, true, attr);
	}
	buff.setColor(COL_WHITE, COL_LIGHT_GRAY);
}

void StagePrinter::deadAnimation(Monster *m) {
	CurPos mapping_pos;
	mapping_coordinate(m->pos, mapping_pos);
	buff.setCursorPos(mapping_pos.first, mapping_pos.second);
	for (int y = 0; y < BOARD_HT; ++y) {
		bool printval = false;
		int i = 0;
		do {
			if (i == 2) {
				printval = true;
			}
			Sleep(5);
			buff.setColor(COL_WHITE, COL_LIGHT_GRAY);
			buff.setCursorPos(mapping_pos.first, mapping_pos.second + i);
			line_write(false, false, m->getAttr());
			i++;
		} while (i <= y);
		buff.swap();
	}
	Sleep(400);
}


void StagePrinter::result(bool clear)
{
	buff.swap();
	buff.clearBuff();
	buff.swap();
	buff.clearBuff();
	TextBox tb(40, 20, &buff);
	CurPos size;
	buff.getBuffSize(size);
	tb.flame_bg = COL_LIGHT_GRAY;
	int x = size.first / 4;
	tb.animation(x + 8, 13);
	buff.swap();
	int i = 4;
	i = i + x;
	CurPos init;
	init.first = 2;
	init.second = i;
	int fg = COL_LIGHT_GRAY;
	int bg = COL_LIGHT_GRAY;
	drawChar(drow18, 7, 9, init, fg, bg);
	i += 9;
	init.first = 2;
	init.second = i;
	drawChar(drow5, 7, 9, init, fg, bg);
	i += 9;
	init.first = 2;
	init.second = i;
	drawChar(drow19, 7, 9, init, fg, bg);
	i += 9;
	init.first = 2;
	init.second = i;
	drawChar(drow21, 7, 9, init, fg, bg);
	i += 9;
	init.first = 2;
	init.second = i;
	drawChar(drow12, 7, 9, init, fg, bg);
	i += 9;
	init.first = 2;
	init.second = i;
	drawChar(drow20, 7, 9, init, fg, bg);
	buff.setColor(COL_BLACK, COL_WHITE);
	string str("");
	int clear_num = s->stage_number;
	if (!clear) {
		clear_num--;
	}
	buff.setCursorPos(x + 13, 16);
	str = "ステージクリア数:" + to_string(clear_num) + "	";
	buff.write(str);
	buff.setCursorPos(x + 13, 18);
	str = "残り残機:" + to_string(s->yuki_life);
	buff.write(str);
	buff.setCursorPos(x + 13, 20);
	str = "倒した敵の数:" + to_string(s->victory_enemy);
	buff.write(str);
	int score = s->victory_enemy * 100 + s->yuki_life * 10;
	buff.setCursorPos(x + 13, 22);
	if (!clear) {
		score *= 0;
	}
	str = "総合スコア:" + to_string(score);
	buff.write(str);
	CurPos evalu_pos;
	evalu_pos.first = 25;
	evalu_pos.second = x + 25;
	if (!clear) {
		drawChar(drow24, 7, 9, evalu_pos, COL_BLACK, COL_BLACK);
	}
	else if (score >= 1900) {
		drawChar(drow19, 7, 9, evalu_pos, COL_DARK_VIOLET, COL_DARK_VIOLET);
	}
	else if (score >= 1500) {
		drawChar(drow1, 7, 9, evalu_pos, COL_DARK_RED, COL_DARK_RED);
	}
	else if (score >= 1100) {
		drawChar(drow2, 7, 9, evalu_pos, COL_DARK_BLUE, COL_DARK_BLUE);
	}
	else {
		drawChar(drow3, 7, 9, evalu_pos, COL_DARK_YELLOW, COL_DARK_YELLOW);
	}

	buff.swap();
	Sleep(200);
	while (true) {
		if (GetAsyncKeyState(VK_RETURN)) {
			if (clear) {
				Sleep(500);
				buff.swap();
				buff.clearBuff();
				flowing_message("魔王…ぐぉお…強くなったのだなYUKIよ。\n\nYUKI…！？なぜ僕の名前を知っている！\n\n魔王…知っているとも、お前が生まれた時から知っている。\n\nYUKI…お前はいったい何者なんだよ！\n\n魔王…そうだな…。もう教えてあげてもいいのではないか？なぁ姫様？\n\nYUKI…え!\n\nAI姫…・・・そうですね。YUKI君落ち着いて聞いてね。魔王はあなたのお兄さんなのよ。\n\nYUKI…えぇ！？なんだって！！！\n\n魔王…まあ大魔王の子ではあるが、人間との間の子でな…。俺とは腹違いだ。\n\nYUKI…なぜ今さらそんなこというんだよ！この何十年間で会える日なんていくらでもあったじゃないかなのにどうして・・・。\n\n魔王…我自身知らなかった…いや記憶を消されていたというのが正しいか。\n\nYUKI…記憶が？\n\n魔王…そうだ。魔界に人間の子がいるとなれば戦争の火種になる可能性があるからな。\nその要因を1つでも消すために関わっていた2人を除いた全員の記憶を消したということだ。\n\nYUKI…その2人はまさか…\n\n魔王…そのまさかだ人間界の現国王と我の父大魔王だ。まあ現国王はきちんと約束を守ってくれたらしいな娘にすら教えなかったのだから。\n\nAI姫…私も連れ去られる前にそのことを聞かされました。思い当たる節はいろいろありましたが、まさかこのようなことがあったとは知りませんでした・・・。\n\nYUKI…連れ去る前？一体どういうことだ…しかも今回の事件いったい何の理由があってこんなことしたんだ？。\n\nAI姫…そっそれは・・・・///");
				Sleep(500);
				buff.swap();
				buff.clearBuff();
				flowing_message("魔王…はぁ・・・YUKI、姫と付き合っているそうじゃないか。\n\nYUKI…なんでそんなこと知っているんだ？\n\n魔王…国王から聞いた。\n\nYUKI…えﾞ秘密にしておいたはずなのに…\n\n魔王…全部バレバレだったらしいぞ・・・。\n\nYUKI…そんなぁ\n\n魔王…そんなことよりもお前ら付き合っているのに手も繋がないとはどういうことなんださっき聞いてみれば1年も進展がないと姫様が嘆いてたぞ\n\nAI姫…/////\n\nYUKI…だだだだって一国の王女だし僕には釣り合わないと思っていたし、姫様の笑顔が見れるだけでよかったというか・・・。\n\n魔王…我が弟ではあるがなんともヘタレなやつだな。\n\nYUKI…ヘタレ言うな！\n\n魔王…お前がヘタレなせいで、YUKIが本当に姫様のことを好いているのか不安になってしまってなそのことについて父と我に相談されてしまったのだ。\nこの時に我の記憶操作が解けてしまうとは思いもしなかったがな。\n\nYUKI…えっ！？国王と姫様とそんな関係なの！！！？\n\n魔王…当然だろう。秘密を共有しお前とその母を預かってほしいと頼んだのは大魔王だぞ仲良くなければそんなことできないであろう。\nまあそのことは今後じっくり話してやる。今はお前と姫様の問題だ！お前は姫様の事好きなのか？嫌いなのか？\n\nYUKI…それは・・・・・す・・・好きですけど・・・・\n\n魔王…魔王の子で我が弟であるぞ！もっと堂々としろ！先ほどの接吻した時の威勢を見せてみろろ！\n\n");
				Sleep(500);
				buff.swap();
				buff.clearBuff();
				flowing_message("YUKI…！？～～～！！！・・・・姫様のことがすきだぁぁぁぁ！！！！\n\nAI姫…////\n\n魔王…うむその度胸こそ魔王にして我が弟であるぞ！して・・・姫様はどうなのだ？\n\nAI姫…私はYUKI君がそばにいてくれた時からずっと好いていましたよ。\n\nYUKI…/////\n\nAI姫…////\n\n魔王…だがもしお前がこの旅で無様に負けて国に帰りでもしたら、我が姫様を嫁として貰っていたがな！\n\nYUKI…まじですか・・・・。\n\n魔王…冗談だ。\n\nAI姫…これにて一件落着ですね/////\n\nみんな仲良くはっぴーえんど");
				Sleep(1000);
				buff.swap();
				buff.clearBuff();
				break;
			}
			else {
				Sleep(500);
				buff.swap();
				buff.clearBuff();
				flowing_message("国王…YUKIよ負けてしまうとは、なんとも情けない。\n\n国王…お前のAIへの愛はこんなものであったのか？\n・・・・・・まあそんなことはどうでもよい。\n\nYUKI…え？それはいったいどういう―。\n\n国王…お前はAIの恋人にはふさわしくなかったということだな。私は陰ながら応援してはいたが、もう限界だ・・・。\n\nYUKI…一体どういうことなんですか！説明して下さい！\n\n国王…自分に自信が持てない、自分のことにしか頭にないお前に、説明するする舌など持たんよ。\n\nYUKI…！！！！\n\n国王…・・・そうだなぁこれだけは言ってやろう。”娘と魔王は明日結婚する”\n\nYUKI…なっなぜ！\n\n国王…説明する舌は持たないといっただろこれだけでも感謝してほしいね。娘の笑顔”だけ”が見たかったのであろう？\n\nYUKI…そ・・・そんなことは・・・\n\n国王…だってそうであろう？娘がせっかく人と関わる機会を与えたのにお前はそんなこと考えもせず、\n我が国とは離れて暮らし、人とは話さずモンスターとしか関わらない。そんな自分の事しか考えていないお前などこれだけで十分だ。\n\nYUKI…そんな・・・。\n\n国王…わかったのならさっさと出て行ってくれお前のような人間はこの国には不要だ。\n\nYUKI…・・・・・・・・・・・。\n\nそして次の日、魔王とAI姫の結婚が行われた。そのときYUKIの姿はあったという。しかしその日からYUKIを見ることはなくなった。\n‐AI姫の日記‐\n\nBAD END");
				Sleep(1000);
				break;
			}
		}
	}
}

void StagePrinter::show_explanatory_text()
{
	CurPos size;
	int i = 5;
	buff.getBuffSize(size);
	buff.setCursorPos(size.first - 50, i);
	if (s->player_turn) {
		buff.setColor(COL_WHITE, COL_DARK_BLUE);
		buff.write("Player Turn");
	}
	else {
		buff.setColor(COL_WHITE, COL_DARK_RED);
		buff.write("Enemy Turn");
	}
	i += 2;
	buff.setCursorPos(size.first - 50, i);
	buff.setColor(COL_WHITE, COL_BLACK);
	buff.setCursorPos(size.first - 50, i);
	buff.write("YUKI_LIFE: " + to_string(s->yuki_life));
	i += 2;
	buff.setCursorPos(size.first - 50, i);
	buff.write("Stage:" + to_string(s->stage_number));
	i += 3;
	buff.setCursorPos(size.first - 50, i);
	buff.write(string("カーソル移動:[↑][↓][→][←]"));
	i += 2;
	buff.setCursorPos(size.first - 50, i);
	buff.write(string("移動先の決定,モンスターの選択:[ENTER]"));
	i += 2;
	buff.setCursorPos(size.first - 50, i);
	buff.setColor(COL_WHITE, COL_DARK_VIOLET);
	buff.write(string("ステージ特性確認/消去:[h] "));
	i += 3;
	buff.setCursorPos(size.first - 50, i);
	buff.setColor(COL_WHITE, COL_DARK_VIOLET);
	buff.write(string("兄"));
	buff.setColor(COL_WHITE, COL_BLACK);
	buff.write(string(":YUKIの兄(魔王)"));
	i += 2;
	buff.setCursorPos(size.first - 50, i);
	buff.setColor(COL_WHITE, COL_DARK_YELLOW);
	buff.write(string("Ｅ"));
	buff.setColor(COL_WHITE, COL_BLACK);
	buff.write(string(":エネミー"));
	i += 2;
	buff.setCursorPos(size.first - 50, i);
	buff.setColor(COL_WHITE, COL_DARK_RED);
	buff.write(string("グ"));
	buff.setColor(COL_WHITE, COL_BLACK);
	buff.write(string(":味方モンスター[属性グー]"));
	i += 2;
	buff.setCursorPos(size.first - 50, i);
	buff.setColor(COL_WHITE, COL_DARK_GREEN);
	buff.write(string("チ"));
	buff.setColor(COL_WHITE, COL_BLACK);
	buff.write(string(":味方モンスター[属性チョキ]"));
	i += 2;
	buff.setCursorPos(size.first - 50, i);
	buff.setColor(COL_WHITE, COL_DARK_CYAN);
	buff.write(string("パ"));
	buff.setColor(COL_WHITE, COL_BLACK);
	buff.write(string(":味方モンスター[属性パー]"));
}

CurPos StagePrinter::mapping_coordinate(CurPos &now_pos, CurPos &pos)
{
	int array_m_wpos[5] = { 0,10,20,30,40 };
	int array_m_hpos[5] = { 0,5,10,15,20 };
	pos.first = array_m_wpos[now_pos.first - 1];
	pos.second = array_m_hpos[now_pos.second - 1] + 2;
	return pos;
}

void StagePrinter::DrawMonsterAnimation(int attr, CurPos now_pos, CurPos next_pos)
{
	CurPos n_mappintg_pos;
	mapping_coordinate(now_pos, n_mappintg_pos);
	int w = n_mappintg_pos.first;
	int v = n_mappintg_pos.second;
	CurPos next_mapping_pos;
	mapping_coordinate(next_pos, next_mapping_pos);
	int next_w = next_mapping_pos.first;
	int next_h = next_mapping_pos.second;
	int i = 2;
	int t = 1;
	if (w > next_w) {
		i *= -1;
	}

	if (v > next_h) {
		t *= -1;
	}
	while (true) {
		if (w != next_w) {
			w += i;
		}
		if (v != next_h) {
			v += t;
		}
		print_board();
		draw_board_monsters(now_pos.first, now_pos.second, true);
		DrawMonster(w, v, attr, s->player_curpos);
		buff.swap();
		buff.clearBuff();
		if (w == next_w && v == next_h) {
			Sleep(400);
			break;
		}
	}
}

void StagePrinter::flowing_message(char *text)
{
	int i = 0;
	int len = 0;
	string str("");
	setlocale(LC_CTYPE, "jpn");
	while (text[i] != '\0') {
		len = mblen(&text[i], MB_CUR_MAX);
		if (len == 2) {
			str += text[i];
			str += text[i + 1];
			i++;
		}
		else {
			str += text[i];
		}
		if (GetAsyncKeyState(VK_RETURN)) {
			str = text;
			break;
		}
		buff.setColor(COL_WHITE, COL_DARK_RED);
		buff.setCursorPos(0, 0);
		buff.write("Skipしたい場合にはエンターを押してね ");
		buff.setColor(COL_WHITE, COL_BLACK);
		buff.setCursorPos(0, 1);
		buff.write(str);
		buff.swap();
		buff.clearBuff();
		Sleep(10);
		i++;
	}
	buff.setCursorPos(0, 0);
	buff.setColor(COL_WHITE, COL_DARK_RED);
	buff.write("Skipしたい場合にはエンターを押してね  ");
	buff.setColor(COL_WHITE, COL_BLACK);
	buff.setCursorPos(0, 1);
	buff.write(str);
	buff.setColor(COL_WHITE, COL_DARK_RED);
	buff.write("\n\n次へ進むにはエンターキーを押してください   ");
	buff.swap();
	buff.clearBuff();
	Sleep(1000);

}

void StagePrinter::drawChar(int array[7][9], int y_length, int x_length, CurPos init_pos, int fgCOL, int bgCOL) {
	for (int y = 0; y < y_length; y++) {
		for (int x = 0; x < x_length; x++) {
			buff.setCursorPos((init_pos.second + x), (init_pos.first + y));
			if (array[y][x] == 1) {
				buff.setColor(fgCOL, bgCOL);
				buff.write(" ");
			}
		}
	}
	buff.setColor(COL_BLACK, COL_BLACK);
}

void StagePrinter::startDraw()
{
	int count = 0;
	while (true) {

		int i = 0;

		CurPos size;
		buff.getBuffSize(size);
		int x = size.first / 4;
		i = i + x;
		CurPos init;
		init.first = 2;
		init.second = i;
		int fg = COL_DARK_VIOLET;
		int bg = COL_DARK_VIOLET;
		drawChar(drow13, 7, 9, init, fg, bg);
		i += 9;
		init.first = 2;
		init.second = i;
		drawChar(drow15, 7, 9, init, fg, bg);
		i += 9;
		init.first = 2;
		init.second = i;
		drawChar(drow14, 7, 9, init, fg, bg);
		i += 9;
		init.first = 2;
		init.second = i;
		drawChar(drow19, 7, 9, init, fg, bg);
		i += 9;
		init.first = 2;
		init.second = i;
		drawChar(drow20, 7, 9, init, fg, bg);
		i += 9;
		init.first = 2;
		init.second = i;
		drawChar(drow5, 7, 9, init, fg, bg);
		i += 9;
		init.first = 2;
		init.second = i;
		drawChar(drow18, 7, 9, init, fg, bg);


		int s = 5 + x;
		init.first = 12;
		init.second = s;
		drawChar(drow13, 7, 9, init, fg, bg);
		s += 9;
		init.first = 12;
		init.second = s;
		drawChar(drow1, 7, 9, init, fg, bg);
		s += 9;
		init.first = 12;
		init.second = s;
		drawChar(drow19, 7, 9, init, fg, bg);
		s += 9;
		init.first = 12;
		init.second = s;
		drawChar(drow20, 7, 9, init, fg, bg);
		s += 9;
		init.first = 12;
		init.second = s;
		drawChar(drow5, 7, 9, init, fg, bg);
		s += 9;
		init.first = 12;
		init.second = s;
		drawChar(drow18, 7, 9, init, fg, bg);


		int t = 14 + x;
		init.first = 22;
		init.second = t;
		drawChar(drow25, 7, 9, init, fg, bg);
		t += 9;
		init.first = 22;
		init.second = t;
		drawChar(drow21, 7, 9, init, fg, bg);
		t += 9;
		init.first = 22;
		init.second = t;
		drawChar(drow11, 7, 9, init, fg, bg);
		t += 9;
		init.first = 22;
		init.second = t;
		drawChar(drow9, 7, 9, init, fg, bg);


		buff.setCursorPos(size.first / 2 - 15, size.second - 8);
		count++;
		if (count % 2) {
			buff.setColor(COL_WHITE, COL_BLACK);
			buff.write("Press Enter Key Start YUKI STORY");
		}
		buff.swap();
		Sleep(550);
		buff.clearBuff();
		if (GetAsyncKeyState(VK_RETURN)) {
			Sleep(100);
			break;
		}
	}
}


