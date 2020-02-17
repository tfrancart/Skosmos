{# This is the template for the front page welcome box. You can enter any html here and show different language versions by using the lang value in a twig conditional as demonstrated below. #}

<div class="welcome-box">
  <img src="resource/pics/unesco_logo_en.jpg" style="width:85%;" />

  <div style="margin-top:20px;">
  	<p>Welcome to the diffusion space of UNESCO’s open vocabularies. The <a href="http://vocabularies.unesco.org/">UNESCO Thesaurus</a> is the first vocabulary to be published in SKOS format. More resources will be posted on this platform as they become available. For more information on the UNESCO Thesaurus consult the <a href="{{ request.lang }}/about">About page</a>.</p>
  </div>
  <div style="text-align:center;margin-top:30px;">
  	<a href="http://creativecommons.org/licenses/by-sa/3.0/igo/"><img src="resource/pics/CC-BY-SA_icon.png" style="width:100px;" /></a>
  </div>
</div>
