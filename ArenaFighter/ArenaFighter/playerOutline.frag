uniform sampler2D texture;
uniform vec4 outlineColour;
uniform float outlineThickness;

void main()
{
    vec2 texCoords = gl_TexCoord[0].xy;
    vec4 pixel = texture2D(texture, texCoords);
    
    if (pixel.a == 0.0)
    {
        float maxAlpha = 0.0;
        
        for (float x = -outlineThickness; x <= outlineThickness; x += 1.0)
        {
            for (float y = -outlineThickness; y <= outlineThickness; y += 1.0)
            {
                vec2 offset = vec2(x, y) / outlineThickness / 100.0;
                maxAlpha = max(maxAlpha, texture2D(texture, texCoords + offset).a);
            }
        }
        
        if (maxAlpha > 0.0)
        {
            gl_FragColor = outlineColour * maxAlpha;
        }
        else
        {
            gl_FragColor = pixel;
        }
    }
    else
    {
        gl_FragColor = pixel;
    }
}