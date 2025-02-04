const getAvatarUrl = async (profileIdentifier) => {
    try {
        const response = await fetch('/.netlify/functions/getAvatarUrl', {
            method: 'GET',
            headers: {
                'Content-Type': 'application/json',
                profileIdentifier: profileIdentifier,
            },
        });
        const data = await response.json();
        return data.avatar_url;
    } catch (error) {
        console.error('Error:', error);
    }
};

const setAvatar = async () => {
    const avatarUrl = await getAvatarUrl('lawrencegarciaaa');
    document.getElementById('gravatar-avatar').src = avatarUrl;
};

setAvatar();
