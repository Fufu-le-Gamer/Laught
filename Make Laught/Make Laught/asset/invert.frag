uniform sampler2D texture;

void main()
{
    // Récupère la couleur du pixel actuel
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    
    // Inverse les composantes R, G, B (1.0 - couleur)
    // On multiplie par gl_Color pour garder la teinte du sprite si besoin
    gl_FragColor = vec4(1.0 - pixel.rgb, pixel.a) * gl_Color;
}