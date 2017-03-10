package io.granska.granska.fakeadapter;
/**
 * Created by david on 10/03/17.
 */
public class FakeData {

    public final static String XML_ERROR = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" standalone=\"yes\"?>\n" +
            "<Root>\n" +
            "    <s ref=\"0\">\n" +
            "        <words>4</words>\n" +
            "        <text>Vad heterw du?</text>\n" +
            "        <contents>\n" +
            "            <w no=\"0\" tag=\"97\" lemma=\"vad\">Vad</w>\n" +
            "            <w no=\"1\" tag=\"124\" lemma=\"heterw\">heterw</w>\n" +
            "            <w no=\"2\" tag=\"60\" lemma=\"du\">du</w>\n" +
            "            <w no=\"3\" tag=\"109\" lemma=\"?\">?</w>\n" +
            "        </contents>\n" +
            "    </s>\n" +
            "    <scrutinizer>\n" +
            "        <s ref=\"0\">\n" +
            "            <gramerrors>\n" +
            "                <gramerror>\n" +
            "                    <marked>\n" +
            "                        <emph type=\"red\">heterw </emph>\n" +
            "                    </marked>\n" +
            "                    <rule>stav1@stavning</rule>\n" +
            "                    <info>Misstänkt stavfel</info>\n" +
            "                    <suggestions>\n" +
            "                        <sugg>\n" +
            "                            <emph type=\"green\">heter</emph>\n" +
            "                        </sugg>\n" +
            "                    </suggestions>\n" +
            "                    <marked_section>\n" +
            "                        <mark begin=\"3\" end=\"3\"/>\n" +
            "                    </marked_section>\n" +
            "                </gramerror>\n" +
            "                <gramerror>\n" +
            "                    <marked/>\n" +
            "                    <rule>inget_verb@verb</rule>\n" +
            "                    <info>Verb verkar saknas i satsen. Om detta är en rubrik bör den inte avslutas med punkt.</info>\n" +
            "                    <marked_section>\n" +
            "                        <mark begin=\"2\" end=\"5\"/>\n" +
            "                    </marked_section>\n" +
            "                </gramerror>\n" +
            "            </gramerrors>\n" +
            "        </s>\n" +
            "    </scrutinizer>\n" +
            "    <tags>\n" +
            "        <tag no=\"0\" name=\"nn.neu.sin.def.nom\"/>\n" +
            "        <tag no=\"1\" name=\"nn.utr\"/>\n" +
            "        <tag no=\"2\" name=\"hd.utr/neu.plu.ind\"/>\n" +
            "        <tag no=\"3\" name=\"jj.pos.sms\"/>\n" +
            "        <tag no=\"4\" name=\"dt.utr/neu.plu.def\"/>\n" +
            "        <tag no=\"5\" name=\"hs.def\"/>\n" +
            "        <tag no=\"6\" name=\"jj.kom.utr/neu.sin/plu.ind/def.nom\"/>\n" +
            "        <tag no=\"7\" name=\"jj.pos.utr/neu.plu.ind/def.nom\"/>\n" +
            "        <tag no=\"8\" name=\"dt.utr.sin.ind/def\"/>\n" +
            "        <tag no=\"9\" name=\"dt.utr/neu.sin.def\"/>\n" +
            "        <tag no=\"10\" name=\"nn.neu.plu.ind.gen\"/>\n" +
            "        <tag no=\"11\" name=\"nn\"/>\n" +
            "        <tag no=\"12\" name=\"nn.utr.plu.def.nom\"/>\n" +
            "        <tag no=\"13\" name=\"jj.pos.neu.sin.ind/def.nom\"/>\n" +
            "        <tag no=\"14\" name=\"nn.utr.sin.def.nom.dat\"/>\n" +
            "        <tag no=\"15\" name=\"vb.imp.akt.aux\"/>\n" +
            "        <tag no=\"16\" name=\"ps.utr.sin.def\"/>\n" +
            "        <tag no=\"17\" name=\"jj.pos.utr/neu.plu.ind.nom\"/>\n" +
            "        <tag no=\"18\" name=\"dt.utr/neu.plu.ind/def\"/>\n" +
            "        <tag no=\"19\" name=\"nn.utr.sin.ind.nom.dat\"/>\n" +
            "        <tag no=\"20\" name=\"hd.neu.sin.ind\"/>\n" +
            "        <tag no=\"21\" name=\"vb.prt.sfo.kop\"/>\n" +
            "        <tag no=\"22\" name=\"sen.que\"/>\n" +
            "        <tag no=\"23\" name=\"dt.utr/neu.plu.ind\"/>\n" +
            "        <tag no=\"24\" name=\"nn.neu\"/>\n" +
            "        <tag no=\"25\" name=\"pn.neu.sin.ind.sub/obj\"/>\n" +
            "        <tag no=\"26\" name=\"pn.utr/neu.plu.def.sub/obj\"/>\n" +
            "        <tag no=\"27\" name=\"hp\"/>\n" +
            "        <tag no=\"28\" name=\"ps.utr/neu.sin/plu.def\"/>\n" +
            "        <tag no=\"29\" name=\"pn.utr/neu.plu.def.obj\"/>\n" +
            "        <tag no=\"30\" name=\"vb.prt.akt.aux\"/>\n" +
            "        <tag no=\"31\" name=\"nn.utr.sin.ind.nom\"/>\n" +
            "        <tag no=\"32\" name=\"ro\"/>\n" +
            "        <tag no=\"33\" name=\"nn.utr.plu.def.gen\"/>\n" +
            "        <tag no=\"34\" name=\"nn.neu.plu.ind.nom\"/>\n" +
            "        <tag no=\"35\" name=\"nn.neu.sin.def.gen\"/>\n" +
            "        <tag no=\"36\" name=\"nn.sms\"/>\n" +
            "        <tag no=\"37\" name=\"jj.suv.mas.sin.def.nom\"/>\n" +
            "        <tag no=\"38\" name=\"jj.suv.utr/neu.sin/plu.def.nom\"/>\n" +
            "        <tag no=\"39\" name=\"vb.prs.sfo\"/>\n" +
            "        <tag no=\"40\" name=\"pm.nom\"/>\n" +
            "        <tag no=\"41\" name=\"sen.hea\"/>\n" +
            "        <tag no=\"42\" name=\"nn.utr.sin.def.nom.set\"/>\n" +
            "        <tag no=\"43\" name=\"sn\"/>\n" +
            "        <tag no=\"44\" name=\"ab.kom\"/>\n" +
            "        <tag no=\"45\" name=\"pad\"/>\n" +
            "        <tag no=\"46\" name=\"dt.utr/neu.sin.ind\"/>\n" +
            "        <tag no=\"47\" name=\"vb.imp\"/>\n" +
            "        <tag no=\"48\" name=\"pn.utr.sin.def.sub/obj\"/>\n" +
            "        <tag no=\"49\" name=\"pn.utr.sin.def.obj\"/>\n" +
            "        <tag no=\"50\" name=\"rg.utr/neu.plu.ind/def.nom\"/>\n" +
            "        <tag no=\"51\" name=\"jj.pos.utr/neu.sin.def.nom\"/>\n" +
            "        <tag no=\"52\" name=\"sen.exc\"/>\n" +
            "        <tag no=\"53\" name=\"rg.utr.sin.ind.nom\"/>\n" +
            "        <tag no=\"54\" name=\"vb.prs.akt\"/>\n" +
            "        <tag no=\"55\" name=\"pm.gen\"/>\n" +
            "        <tag no=\"56\" name=\"dt.utr.sin.ind\"/>\n" +
            "        <tag no=\"57\" name=\"dt.utr/neu.sin/plu.ind\"/>\n" +
            "        <tag no=\"58\" name=\"nn.utr.sms\"/>\n" +
            "        <tag no=\"59\" name=\"vb.inf.akt.aux\"/>\n" +
            "        <tag no=\"60\" name=\"pn.utr.sin.def.sub\"/>\n" +
            "        <tag no=\"61\" name=\"kn\"/>\n" +
            "        <tag no=\"62\" name=\"vb.prs.sfo.kop\"/>\n" +
            "        <tag no=\"63\" name=\"vb.prs.akt.mod\"/>\n" +
            "        <tag no=\"64\" name=\"vb.inf.akt.mod\"/>\n" +
            "        <tag no=\"65\" name=\"pc.gen\"/>\n" +
            "        <tag no=\"66\" name=\"ro.nom\"/>\n" +
            "        <tag no=\"67\" name=\"jj.pos.neu.sin.ind.nom\"/>\n" +
            "        <tag no=\"68\" name=\"nn.utr.plu.ind.nom\"/>\n" +
            "        <tag no=\"69\" name=\"pn.utr.sin.ind.sub\"/>\n" +
            "        <tag no=\"70\" name=\"jj.suv.utr/neu.plu.def.nom\"/>\n" +
            "        <tag no=\"71\" name=\"dt.neu.sin.def\"/>\n" +
            "        <tag no=\"72\" name=\"rg.sin\"/>\n" +
            "        <tag no=\"73\" name=\"ro.sin\"/>\n" +
            "        <tag no=\"74\" name=\"vb.imp.akt.kop\"/>\n" +
            "        <tag no=\"75\" name=\"hd.utr.sin.ind\"/>\n" +
            "        <tag no=\"76\" name=\"nn.neu.sin.def.nom.set\"/>\n" +
            "        <tag no=\"77\" name=\"vb.kon.prs.akt\"/>\n" +
            "        <tag no=\"78\" name=\"ab.suv\"/>\n" +
            "        <tag no=\"79\" name=\"vb.inf.akt\"/>\n" +
            "        <tag no=\"80\" name=\"jj.pos.utr.sin.ind.nom\"/>\n" +
            "        <tag no=\"81\" name=\"nn.neu.plu.def.gen\"/>\n" +
            "        <tag no=\"82\" name=\"vb.imp.akt.mod\"/>\n" +
            "        <tag no=\"83\" name=\"vb.prt.akt.mod\"/>\n" +
            "        <tag no=\"84\" name=\"dt.neu.sin.ind\"/>\n" +
            "        <tag no=\"85\" name=\"pn.utr/neu.plu.ind.sub/obj\"/>\n" +
            "        <tag no=\"86\" name=\"pn.neu.sin.def.sub/obj\"/>\n" +
            "        <tag no=\"87\" name=\"vb.inf.akt.kop\"/>\n" +
            "        <tag no=\"88\" name=\"rg.neu.sin.ind.nom\"/>\n" +
            "        <tag no=\"89\" name=\"pn.mas.sin.def.sub/obj\"/>\n" +
            "        <tag no=\"90\" name=\"ro.gen\"/>\n" +
            "        <tag no=\"91\" name=\"nn.neu.plu.def.nom\"/>\n" +
            "        <tag no=\"92\" name=\"dt.mas.sin.ind/def\"/>\n" +
            "        <tag no=\"93\" name=\"dt.neu.sin.ind/def\"/>\n" +
            "        <tag no=\"94\" name=\"vb.inf.sfo\"/>\n" +
            "        <tag no=\"95\" name=\"jj.suv.utr/neu.sin/plu.ind.nom\"/>\n" +
            "        <tag no=\"96\" name=\"rg.gen\"/>\n" +
            "        <tag no=\"97\" name=\"hp.neu.sin.ind\"/>\n" +
            "        <tag no=\"98\" name=\"vb.kon.prt\"/>\n" +
            "        <tag no=\"99\" name=\"sen.per\"/>\n" +
            "        <tag no=\"100\" name=\"ps.utr/neu.plu.def\"/>\n" +
            "        <tag no=\"101\" name=\"nn.utr.sin.ind.nom.set\"/>\n" +
            "        <tag no=\"102\" name=\"nn.utr.sin.def.nom\"/>\n" +
            "        <tag no=\"103\" name=\"pn.utr.plu.def.sub\"/>\n" +
            "        <tag no=\"104\" name=\"nn.neu.sin.ind.gen\"/>\n" +
            "        <tag no=\"105\" name=\"ps.neu.sin.def\"/>\n" +
            "        <tag no=\"106\" name=\"pn.utr.plu.def.obj\"/>\n" +
            "        <tag no=\"107\" name=\"jj.pos.utr.sin.ind/def.nom\"/>\n" +
            "        <tag no=\"108\" name=\"vb.prt.sfo\"/>\n" +
            "        <tag no=\"109\" name=\"mad\"/>\n" +
            "        <tag no=\"110\" name=\"ab\"/>\n" +
            "        <tag no=\"111\" name=\"pn.utr/neu.sin/plu.def.obj\"/>\n" +
            "        <tag no=\"112\" name=\"vb.sup.akt\"/>\n" +
            "        <tag no=\"113\" name=\"mid\"/>\n" +
            "        <tag no=\"114\" name=\"vb.sup.akt.kop\"/>\n" +
            "        <tag no=\"115\" name=\"jj.pos.mas.sin.def.nom\"/>\n" +
            "        <tag no=\"116\" name=\"hp.utr/neu.plu.ind\"/>\n" +
            "        <tag no=\"117\" name=\"vb.sup.akt.mod\"/>\n" +
            "        <tag no=\"118\" name=\"jj.kom.sms\"/>\n" +
            "        <tag no=\"119\" name=\"nn.utr.sin.def.gen\"/>\n" +
            "        <tag no=\"120\" name=\"rg.nom\"/>\n" +
            "        <tag no=\"121\" name=\"nn.neu.sin.ind.nom\"/>\n" +
            "        <tag no=\"122\" name=\"rg.yea\"/>\n" +
            "        <tag no=\"123\" name=\"pl\"/>\n" +
            "        <tag no=\"124\" name=\"in\"/>\n" +
            "        <tag no=\"125\" name=\"vb.prt.akt\"/>\n" +
            "        <tag no=\"126\" name=\"nn.neu.sms\"/>\n" +
            "        <tag no=\"127\" name=\"vb.sup.sfo\"/>\n" +
            "        <tag no=\"128\" name=\"nn.utr.plu.ind.gen\"/>\n" +
            "        <tag no=\"129\" name=\"pn.utr.sin.ind.sub/obj\"/>\n" +
            "        <tag no=\"130\" name=\"dt.utr.sin.def\"/>\n" +
            "        <tag no=\"131\" name=\"nn.neu.sin.ind.nom.set\"/>\n" +
            "        <tag no=\"132\" name=\"vb\"/>\n" +
            "        <tag no=\"133\" name=\"pp\"/>\n" +
            "        <tag no=\"134\" name=\"vb.prs.akt.kop\"/>\n" +
            "        <tag no=\"135\" name=\"nn.utr.sin.ind.gen\"/>\n" +
            "        <tag no=\"136\" name=\"jj.gen\"/>\n" +
            "        <tag no=\"137\" name=\"vb.prt.akt.kop\"/>\n" +
            "        <tag no=\"138\" name=\"ie\"/>\n" +
            "        <tag no=\"139\" name=\"ro.mas.sin.ind/def.nom\"/>\n" +
            "        <tag no=\"140\" name=\"jj.pos.utr/neu.sin/plu.ind/def.nom\"/>\n" +
            "        <tag no=\"141\" name=\"hp.utr.sin.ind\"/>\n" +
            "        <tag no=\"142\" name=\"pc.prs.utr/neu.sin/plu.ind/def.nom\"/>\n" +
            "        <tag no=\"143\" name=\"sen.non\"/>\n" +
            "        <tag no=\"144\" name=\"pn.utr/neu.plu.def.sub\"/>\n" +
            "        <tag no=\"145\" name=\"ha\"/>\n" +
            "        <tag no=\"146\" name=\"vb.prs.akt.aux\"/>\n" +
            "        <tag no=\"147\" name=\"ab.pos\"/>\n" +
            "        <tag no=\"148\" name=\"pm.sms\"/>\n" +
            "    </tags>\n" +
            "    <rules>\n" +
            "        <categories>\n" +
            "            <category>\n" +
            "                <name>a</name>\n" +
            "                <info>diverse</info>\n" +
            "                <count>0</count>\n" +
            "            </category>\n" +
            "            <category>\n" +
            "                <name>prob</name>\n" +
            "                <info>Statistisk grammatikgranskning</info>\n" +
            "                <count>0</count>\n" +
            "            </category>\n" +
            "            <category>\n" +
            "                <name>stavning</name>\n" +
            "                <info>stavning</info>\n" +
            "                <linkurl>http://www.nada.kth.se/~viggo/stava/manual.html</linkurl>\n" +
            "                <linktext>Stava</linktext>\n" +
            "                <count>2</count>\n" +
            "            </category>\n" +
            "            <category>\n" +
            "                <name>stil</name>\n" +
            "                <info>stilkontroll</info>\n" +
            "                <count>0</count>\n" +
            "            </category>\n" +
            "            <category>\n" +
            "                <name>byråkrat</name>\n" +
            "                <info>formellt uttryck</info>\n" +
            "                <count>0</count>\n" +
            "            </category>\n" +
            "            <category>\n" +
            "                <name>pronomen</name>\n" +
            "                <info>felaktig pronomenform</info>\n" +
            "                <count>0</count>\n" +
            "            </category>\n" +
            "            <category>\n" +
            "                <name>adjektiv</name>\n" +
            "                <info>felaktig adjektivfras</info>\n" +
            "                <count>0</count>\n" +
            "            </category>\n" +
            "            <category>\n" +
            "                <name>sammanblandning</name>\n" +
            "                <info>sammanblandning av uttryck</info>\n" +
            "                <count>0</count>\n" +
            "            </category>\n" +
            "            <category>\n" +
            "                <name>sär</name>\n" +
            "                <info>Misstänkt särskrivning</info>\n" +
            "                <count>0</count>\n" +
            "            </category>\n" +
            "            <category>\n" +
            "                <name>kong</name>\n" +
            "                <info>kongruensfel</info>\n" +
            "                <count>0</count>\n" +
            "            </category>\n" +
            "            <category>\n" +
            "                <name>pred</name>\n" +
            "                <info>kongruensfel i predikativ</info>\n" +
            "                <count>0</count>\n" +
            "            </category>\n" +
            "            <category>\n" +
            "                <name>verb</name>\n" +
            "                <info>underlig verbkonstruktion</info>\n" +
            "                <count>2</count>\n" +
            "            </category>\n" +
            "            <category>\n" +
            "                <name>ordföljd</name>\n" +
            "                <info>underlig ordföljd</info>\n" +
            "                <count>0</count>\n" +
            "            </category>\n" +
            "            <category>\n" +
            "                <name>negation</name>\n" +
            "                <info>underlig negation</info>\n" +
            "                <count>0</count>\n" +
            "            </category>\n" +
            "            <category>\n" +
            "                <name>prep</name>\n" +
            "                <info>ovanligt prepositionsbruk</info>\n" +
            "                <count>0</count>\n" +
            "            </category>\n" +
            "            <category>\n" +
            "                <name>lexin_verb</name>\n" +
            "                <info>underlig verbkonstruktion</info>\n" +
            "                <count>0</count>\n" +
            "            </category>\n" +
            "        </categories>\n" +
            "        <rules_used>\n" +
            "            <rule>\n" +
            "                <name>stav1@stavning</name>\n" +
            "                <category>stavning</category>\n" +
            "                <linkurl>http://www.nada.kth.se/~viggo/stava/manual.html</linkurl>\n" +
            "                <linktext>Stava</linktext>\n" +
            "            </rule>\n" +
            "            <rule>\n" +
            "                <name>inget_verb@verb</name>\n" +
            "                <category>verb</category>\n" +
            "            </rule>\n" +
            "        </rules_used>\n" +
            "    </rules>\n" +
            "</Root>\n";

    public final static String XML = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" standalone=\"yes\"?><Root><s ref=\"0\"><words>4</words>\n" +
            "<text>Vad heter du?</text>\n" +
            "<contents><w no=\"0\" tag=\"97\" lemma=\"vad\">Vad</w>\n" +
            "<w no=\"1\" tag=\"134\" lemma=\"heta\">heter</w>\n" +
            "<w no=\"2\" tag=\"60\" lemma=\"du\">du</w>\n" +
            "<w no=\"3\" tag=\"109\" lemma=\"?\">?</w>\n" +
            "</contents>\n" +
            "</s>\n" +
            "<scrutinizer></scrutinizer>\n" +
            "<tags><tag no=\"0\" name=\"nn.neu.sin.def.nom\"/>\n" +
            "<tag no=\"1\" name=\"nn.utr\"/>\n" +
            "<tag no=\"2\" name=\"hd.utr/neu.plu.ind\"/>\n" +
            "<tag no=\"3\" name=\"jj.pos.sms\"/>\n" +
            "<tag no=\"4\" name=\"dt.utr/neu.plu.def\"/>\n" +
            "<tag no=\"5\" name=\"hs.def\"/>\n" +
            "<tag no=\"6\" name=\"jj.kom.utr/neu.sin/plu.ind/def.nom\"/>\n" +
            "<tag no=\"7\" name=\"jj.pos.utr/neu.plu.ind/def.nom\"/>\n" +
            "<tag no=\"8\" name=\"dt.utr.sin.ind/def\"/>\n" +
            "<tag no=\"9\" name=\"dt.utr/neu.sin.def\"/>\n" +
            "<tag no=\"10\" name=\"nn.neu.plu.ind.gen\"/>\n" +
            "<tag no=\"11\" name=\"nn\"/>\n" +
            "<tag no=\"12\" name=\"nn.utr.plu.def.nom\"/>\n" +
            "<tag no=\"13\" name=\"jj.pos.neu.sin.ind/def.nom\"/>\n" +
            "<tag no=\"14\" name=\"nn.utr.sin.def.nom.dat\"/>\n" +
            "<tag no=\"15\" name=\"vb.imp.akt.aux\"/>\n" +
            "<tag no=\"16\" name=\"ps.utr.sin.def\"/>\n" +
            "<tag no=\"17\" name=\"jj.pos.utr/neu.plu.ind.nom\"/>\n" +
            "<tag no=\"18\" name=\"dt.utr/neu.plu.ind/def\"/>\n" +
            "<tag no=\"19\" name=\"nn.utr.sin.ind.nom.dat\"/>\n" +
            "<tag no=\"20\" name=\"hd.neu.sin.ind\"/>\n" +
            "<tag no=\"21\" name=\"vb.prt.sfo.kop\"/>\n" +
            "<tag no=\"22\" name=\"sen.que\"/>\n" +
            "<tag no=\"23\" name=\"dt.utr/neu.plu.ind\"/>\n" +
            "<tag no=\"24\" name=\"nn.neu\"/>\n" +
            "<tag no=\"25\" name=\"pn.neu.sin.ind.sub/obj\"/>\n" +
            "<tag no=\"26\" name=\"pn.utr/neu.plu.def.sub/obj\"/>\n" +
            "<tag no=\"27\" name=\"hp\"/>\n" +
            "<tag no=\"28\" name=\"ps.utr/neu.sin/plu.def\"/>\n" +
            "<tag no=\"29\" name=\"pn.utr/neu.plu.def.obj\"/>\n" +
            "<tag no=\"30\" name=\"vb.prt.akt.aux\"/>\n" +
            "<tag no=\"31\" name=\"nn.utr.sin.ind.nom\"/>\n" +
            "<tag no=\"32\" name=\"ro\"/>\n" +
            "<tag no=\"33\" name=\"nn.utr.plu.def.gen\"/>\n" +
            "<tag no=\"34\" name=\"nn.neu.plu.ind.nom\"/>\n" +
            "<tag no=\"35\" name=\"nn.neu.sin.def.gen\"/>\n" +
            "<tag no=\"36\" name=\"nn.sms\"/>\n" +
            "<tag no=\"37\" name=\"jj.suv.mas.sin.def.nom\"/>\n" +
            "<tag no=\"38\" name=\"jj.suv.utr/neu.sin/plu.def.nom\"/>\n" +
            "<tag no=\"39\" name=\"vb.prs.sfo\"/>\n" +
            "<tag no=\"40\" name=\"pm.nom\"/>\n" +
            "<tag no=\"41\" name=\"sen.hea\"/>\n" +
            "<tag no=\"42\" name=\"nn.utr.sin.def.nom.set\"/>\n" +
            "<tag no=\"43\" name=\"sn\"/>\n" +
            "<tag no=\"44\" name=\"ab.kom\"/>\n" +
            "<tag no=\"45\" name=\"pad\"/>\n" +
            "<tag no=\"46\" name=\"dt.utr/neu.sin.ind\"/>\n" +
            "<tag no=\"47\" name=\"vb.imp\"/>\n" +
            "<tag no=\"48\" name=\"pn.utr.sin.def.sub/obj\"/>\n" +
            "<tag no=\"49\" name=\"pn.utr.sin.def.obj\"/>\n" +
            "<tag no=\"50\" name=\"rg.utr/neu.plu.ind/def.nom\"/>\n" +
            "<tag no=\"51\" name=\"jj.pos.utr/neu.sin.def.nom\"/>\n" +
            "<tag no=\"52\" name=\"sen.exc\"/>\n" +
            "<tag no=\"53\" name=\"rg.utr.sin.ind.nom\"/>\n" +
            "<tag no=\"54\" name=\"vb.prs.akt\"/>\n" +
            "<tag no=\"55\" name=\"pm.gen\"/>\n" +
            "<tag no=\"56\" name=\"dt.utr.sin.ind\"/>\n" +
            "<tag no=\"57\" name=\"dt.utr/neu.sin/plu.ind\"/>\n" +
            "<tag no=\"58\" name=\"nn.utr.sms\"/>\n" +
            "<tag no=\"59\" name=\"vb.inf.akt.aux\"/>\n" +
            "<tag no=\"60\" name=\"pn.utr.sin.def.sub\"/>\n" +
            "<tag no=\"61\" name=\"kn\"/>\n" +
            "<tag no=\"62\" name=\"vb.prs.sfo.kop\"/>\n" +
            "<tag no=\"63\" name=\"vb.prs.akt.mod\"/>\n" +
            "<tag no=\"64\" name=\"vb.inf.akt.mod\"/>\n" +
            "<tag no=\"65\" name=\"pc.gen\"/>\n" +
            "<tag no=\"66\" name=\"ro.nom\"/>\n" +
            "<tag no=\"67\" name=\"jj.pos.neu.sin.ind.nom\"/>\n" +
            "<tag no=\"68\" name=\"nn.utr.plu.ind.nom\"/>\n" +
            "<tag no=\"69\" name=\"pn.utr.sin.ind.sub\"/>\n" +
            "<tag no=\"70\" name=\"jj.suv.utr/neu.plu.def.nom\"/>\n" +
            "<tag no=\"71\" name=\"dt.neu.sin.def\"/>\n" +
            "<tag no=\"72\" name=\"rg.sin\"/>\n" +
            "<tag no=\"73\" name=\"ro.sin\"/>\n" +
            "<tag no=\"74\" name=\"vb.imp.akt.kop\"/>\n" +
            "<tag no=\"75\" name=\"hd.utr.sin.ind\"/>\n" +
            "<tag no=\"76\" name=\"nn.neu.sin.def.nom.set\"/>\n" +
            "<tag no=\"77\" name=\"vb.kon.prs.akt\"/>\n" +
            "<tag no=\"78\" name=\"ab.suv\"/>\n" +
            "<tag no=\"79\" name=\"vb.inf.akt\"/>\n" +
            "<tag no=\"80\" name=\"jj.pos.utr.sin.ind.nom\"/>\n" +
            "<tag no=\"81\" name=\"nn.neu.plu.def.gen\"/>\n" +
            "<tag no=\"82\" name=\"vb.imp.akt.mod\"/>\n" +
            "<tag no=\"83\" name=\"vb.prt.akt.mod\"/>\n" +
            "<tag no=\"84\" name=\"dt.neu.sin.ind\"/>\n" +
            "<tag no=\"85\" name=\"pn.utr/neu.plu.ind.sub/obj\"/>\n" +
            "<tag no=\"86\" name=\"pn.neu.sin.def.sub/obj\"/>\n" +
            "<tag no=\"87\" name=\"vb.inf.akt.kop\"/>\n" +
            "<tag no=\"88\" name=\"rg.neu.sin.ind.nom\"/>\n" +
            "<tag no=\"89\" name=\"pn.mas.sin.def.sub/obj\"/>\n" +
            "<tag no=\"90\" name=\"ro.gen\"/>\n" +
            "<tag no=\"91\" name=\"nn.neu.plu.def.nom\"/>\n" +
            "<tag no=\"92\" name=\"dt.mas.sin.ind/def\"/>\n" +
            "<tag no=\"93\" name=\"dt.neu.sin.ind/def\"/>\n" +
            "<tag no=\"94\" name=\"vb.inf.sfo\"/>\n" +
            "<tag no=\"95\" name=\"jj.suv.utr/neu.sin/plu.ind.nom\"/>\n" +
            "<tag no=\"96\" name=\"rg.gen\"/>\n" +
            "<tag no=\"97\" name=\"hp.neu.sin.ind\"/>\n" +
            "<tag no=\"98\" name=\"vb.kon.prt\"/>\n" +
            "<tag no=\"99\" name=\"sen.per\"/>\n" +
            "<tag no=\"100\" name=\"ps.utr/neu.plu.def\"/>\n" +
            "<tag no=\"101\" name=\"nn.utr.sin.ind.nom.set\"/>\n" +
            "<tag no=\"102\" name=\"nn.utr.sin.def.nom\"/>\n" +
            "<tag no=\"103\" name=\"pn.utr.plu.def.sub\"/>\n" +
            "<tag no=\"104\" name=\"nn.neu.sin.ind.gen\"/>\n" +
            "<tag no=\"105\" name=\"ps.neu.sin.def\"/>\n" +
            "<tag no=\"106\" name=\"pn.utr.plu.def.obj\"/>\n" +
            "<tag no=\"107\" name=\"jj.pos.utr.sin.ind/def.nom\"/>\n" +
            "<tag no=\"108\" name=\"vb.prt.sfo\"/>\n" +
            "<tag no=\"109\" name=\"mad\"/>\n" +
            "<tag no=\"110\" name=\"ab\"/>\n" +
            "<tag no=\"111\" name=\"pn.utr/neu.sin/plu.def.obj\"/>\n" +
            "<tag no=\"112\" name=\"vb.sup.akt\"/>\n" +
            "<tag no=\"113\" name=\"mid\"/>\n" +
            "<tag no=\"114\" name=\"vb.sup.akt.kop\"/>\n" +
            "<tag no=\"115\" name=\"jj.pos.mas.sin.def.nom\"/>\n" +
            "<tag no=\"116\" name=\"hp.utr/neu.plu.ind\"/>\n" +
            "<tag no=\"117\" name=\"vb.sup.akt.mod\"/>\n" +
            "<tag no=\"118\" name=\"jj.kom.sms\"/>\n" +
            "<tag no=\"119\" name=\"nn.utr.sin.def.gen\"/>\n" +
            "<tag no=\"120\" name=\"rg.nom\"/>\n" +
            "<tag no=\"121\" name=\"nn.neu.sin.ind.nom\"/>\n" +
            "<tag no=\"122\" name=\"rg.yea\"/>\n" +
            "<tag no=\"123\" name=\"pl\"/>\n" +
            "<tag no=\"124\" name=\"in\"/>\n" +
            "<tag no=\"125\" name=\"vb.prt.akt\"/>\n" +
            "<tag no=\"126\" name=\"nn.neu.sms\"/>\n" +
            "<tag no=\"127\" name=\"vb.sup.sfo\"/>\n" +
            "<tag no=\"128\" name=\"nn.utr.plu.ind.gen\"/>\n" +
            "<tag no=\"129\" name=\"pn.utr.sin.ind.sub/obj\"/>\n" +
            "<tag no=\"130\" name=\"dt.utr.sin.def\"/>\n" +
            "<tag no=\"131\" name=\"nn.neu.sin.ind.nom.set\"/>\n" +
            "<tag no=\"132\" name=\"vb\"/>\n" +
            "<tag no=\"133\" name=\"pp\"/>\n" +
            "<tag no=\"134\" name=\"vb.prs.akt.kop\"/>\n" +
            "<tag no=\"135\" name=\"nn.utr.sin.ind.gen\"/>\n" +
            "<tag no=\"136\" name=\"jj.gen\"/>\n" +
            "<tag no=\"137\" name=\"vb.prt.akt.kop\"/>\n" +
            "<tag no=\"138\" name=\"ie\"/>\n" +
            "<tag no=\"139\" name=\"ro.mas.sin.ind/def.nom\"/>\n" +
            "<tag no=\"140\" name=\"jj.pos.utr/neu.sin/plu.ind/def.nom\"/>\n" +
            "<tag no=\"141\" name=\"hp.utr.sin.ind\"/>\n" +
            "<tag no=\"142\" name=\"pc.prs.utr/neu.sin/plu.ind/def.nom\"/>\n" +
            "<tag no=\"143\" name=\"sen.non\"/>\n" +
            "<tag no=\"144\" name=\"pn.utr/neu.plu.def.sub\"/>\n" +
            "<tag no=\"145\" name=\"ha\"/>\n" +
            "<tag no=\"146\" name=\"vb.prs.akt.aux\"/>\n" +
            "<tag no=\"147\" name=\"ab.pos\"/>\n" +
            "<tag no=\"148\" name=\"pm.sms\"/>\n" +
            "</tags>\n" +
            "<rules><categories><category><name>a</name>\n" +
            "<info>diverse</info>\n" +
            "<count>0</count>\n" +
            "</category>\n" +
            "<category><name>prob</name>\n" +
            "<info>Statistisk grammatikgranskning</info>\n" +
            "<count>0</count>\n" +
            "</category>\n" +
            "<category><name>stavning</name>\n" +
            "<info>stavning</info>\n" +
            "<linkurl>http://www.nada.kth.se/~viggo/stava/manual.html</linkurl>\n" +
            "<linktext>Stava</linktext>\n" +
            "<count>2</count>\n" +
            "</category>\n" +
            "<category><name>stil</name>\n" +
            "<info>stilkontroll</info>\n" +
            "<count>0</count>\n" +
            "</category>\n" +
            "<category><name>byråkrat</name>\n" +
            "<info>formellt uttryck</info>\n" +
            "<count>0</count>\n" +
            "</category>\n" +
            "<category><name>pronomen</name>\n" +
            "<info>felaktig pronomenform</info>\n" +
            "<count>0</count>\n" +
            "</category>\n" +
            "<category><name>adjektiv</name>\n" +
            "<info>felaktig adjektivfras</info>\n" +
            "<count>0</count>\n" +
            "</category>\n" +
            "<category><name>sammanblandning</name>\n" +
            "<info>sammanblandning av uttryck</info>\n" +
            "<count>0</count>\n" +
            "</category>\n" +
            "<category><name>sär</name>\n" +
            "<info>Misstänkt särskrivning</info>\n" +
            "<count>0</count>\n" +
            "</category>\n" +
            "<category><name>kong</name>\n" +
            "<info>kongruensfel</info>\n" +
            "<count>0</count>\n" +
            "</category>\n" +
            "<category><name>pred</name>\n" +
            "<info>kongruensfel i predikativ</info>\n" +
            "<count>0</count>\n" +
            "</category>\n" +
            "<category><name>verb</name>\n" +
            "<info>underlig verbkonstruktion</info>\n" +
            "<count>0</count>\n" +
            "</category>\n" +
            "<category><name>ordföljd</name>\n" +
            "<info>underlig ordföljd</info>\n" +
            "<count>0</count>\n" +
            "</category>\n" +
            "<category><name>negation</name>\n" +
            "<info>underlig negation</info>\n" +
            "<count>0</count>\n" +
            "</category>\n" +
            "<category><name>prep</name>\n" +
            "<info>ovanligt prepositionsbruk</info>\n" +
            "<count>0</count>\n" +
            "</category>\n" +
            "<category><name>lexin_verb</name>\n" +
            "<info>underlig verbkonstruktion</info>\n" +
            "<count>0</count>\n" +
            "</category>\n" +
            "</categories>\n" +
            "<rules_used><rule><name>stav1@stavning</name>\n" +
            "<category>stavning</category>\n" +
            "<linkurl>http://www.nada.kth.se/~viggo/stava/manual.html</linkurl>\n" +
            "<linktext>Stava</linktext>\n" +
            "</rule>\n" +
            "</rules_used>\n" +
            "</rules>\n" +
            "</Root>";
}
